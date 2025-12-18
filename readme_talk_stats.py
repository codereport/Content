#!/usr/bin/env python3
"""
Script to analyze talk statistics from README.md
Counts total talks and talks with recordings from the Conference Talks table.
Also tracks countries visited by year.
Generates an HTML page with the statistics.
"""

import re
import sys
import webbrowser
import tempfile
from pathlib import Path
from collections import defaultdict

# Talk location types
LOCATION_COUNTRY = "country"
LOCATION_ONLINE = "online"
LOCATION_YOUTUBE = "youtube"

# Map ISO codes to country names (for display)
ISO_TO_COUNTRY = {
    "US": "USA",
    "GB": "UK",
    "DE": "Germany",
    "PL": "Poland",
    "CA": "Canada",
    "HU": "Hungary",
    "NO": "Norway",
    "ES": "Spain",
    "NL": "Netherlands",
    "DK": "Denmark",
    "AU": "Australia",
    "IT": "Italy",
}

# Map country names to ISO codes (legacy support)
COUNTRY_TO_ISO = {v: k for k, v in ISO_TO_COUNTRY.items()}


def flag_to_iso(flag):
    """Convert a flag emoji to its ISO code."""
    if len(flag) != 2:
        return None
    try:
        # Regional indicator symbols start at 0x1F1E6 for 'A'
        first = ord(flag[0]) - 0x1F1E6
        second = ord(flag[1]) - 0x1F1E6
        if 0 <= first <= 25 and 0 <= second <= 25:
            return chr(ord("A") + first) + chr(ord("A") + second)
    except (TypeError, ValueError):
        pass
    return None


def flag_to_country(flag):
    """Convert a flag emoji to country name."""
    iso = flag_to_iso(flag)
    return ISO_TO_COUNTRY.get(iso, iso) if iso else None


def country_to_flag(country):
    """Convert a country name or ISO code to its flag emoji."""
    # If it's already a flag emoji, return it
    if country and len(country) == 2 and ord(country[0]) >= 0x1F1E6:
        return country
    # Try as country name first
    iso_code = COUNTRY_TO_ISO.get(country, "")
    # If not found, try as ISO code directly
    if not iso_code and country and len(country) == 2:
        iso_code = country.upper()
    if not iso_code:
        return ""
    # Convert ISO code to regional indicator symbols (flag emoji)
    return "".join(chr(0x1F1E6 + ord(c) - ord("A")) for c in iso_code)


def extract_country(location):
    """Extract country from location string like 'Santa Clara, 🇺🇸' or '🇦🇺'."""
    if not location or location.lower() in ("online", "youtube"):
        return None

    location = location.strip()

    # If there's a comma, take the part after the last comma
    if "," in location:
        country_part = location.split(",")[-1].strip()
    else:
        country_part = location

    # Check if it's a flag emoji (2 regional indicator symbols)
    if len(country_part) >= 2:
        # Try to parse as flag emoji
        potential_flag = country_part[:2]
        if ord(potential_flag[0]) >= 0x1F1E6:
            return potential_flag

    # Legacy: check if it's a country name
    if country_part in COUNTRY_TO_ISO:
        return country_to_flag(country_part)

    return None


def get_location_type(location, conference_name=""):
    """Determine the type of location: country, online (Zoom), or youtube."""
    loc_lower = location.strip().lower() if location else ""
    conf_lower = conference_name.lower() if conference_name else ""

    # YouTube if location or conference name contains "youtube"
    if "youtube" in loc_lower or "youtube" in conf_lower:
        return LOCATION_YOUTUBE
    if not location or loc_lower == "online":
        return LOCATION_ONLINE
    return LOCATION_COUNTRY


def parse_conference_talks_table(readme_content):
    """
    Parse the Conference Talks markdown table and extract statistics.

    Returns:
        tuple: (total_talks, talks_with_recordings, conference_talks, meetup_talks,
                conferences_with_recordings, meetups_with_recordings, countries_by_year,
                talks_by_year)
    """
    lines = readme_content.split("\n")

    # Find the Conference Talks table
    table_start = None
    table_end = None

    for i, line in enumerate(lines):
        if "## Conference Talks" in line:
            # Look for the table header (flexible matching)
            for j in range(i, min(i + 10, len(lines))):
                # Check if line contains the key column headers
                line_lower = lines[j].lower().replace(" ", "")
                if (
                    "conference/meetup" in line_lower
                    and "year" in line_lower
                    and "location" in line_lower
                ):
                    table_start = j + 2  # Skip header and separator
                    break
            break

    if table_start is None:
        raise ValueError("Could not find Conference Talks table")

    # Find where the table ends (next section or empty line)
    for i in range(table_start, len(lines)):
        line = lines[i].strip()
        if (
            not line
            or not line.startswith("|")
            or line.startswith("1 -")
            or line.startswith("\\*")
        ):
            table_end = i
            break

    if table_end is None:
        table_end = len(lines)

    # Parse table rows
    total_talks = 0
    talks_with_recordings = 0
    conference_talks = 0
    meetup_talks = 0
    conferences_with_recordings = 0
    meetups_with_recordings = 0
    countries_by_year = defaultdict(set)
    talks_by_year = defaultdict(list)  # List of (month, country_or_online) tuples

    for i in range(table_start, table_end):
        line = lines[i].strip()
        if not line or not line.startswith("|"):
            continue

        # Split the table row
        columns = [
            col.strip() for col in line.split("|")[1:-1]
        ]  # Remove empty first/last elements

        if len(columns) < 4:
            continue

        conference_meetup = columns[0]
        year_col = columns[1]
        location_col = columns[2]
        talk_column = columns[3]

        # Count total talks
        total_talks += 1

        # Extract year and month (format: 2019-05 -> year=2019, month=05)
        parts = year_col.split("-")
        year = parts[0]
        month = parts[1] if len(parts) > 1 else "01"

        # Extract country
        country = extract_country(location_col)
        if country:
            countries_by_year[year].add(country)

        # Track each talk for the talks-by-year display
        location_type = get_location_type(location_col, conference_meetup)
        talks_by_year[year].append((month, location_type, country))

        # Check if it's a conference or meetup
        is_conference = ":green_heart:" in conference_meetup
        is_meetup = ":blue_heart:" in conference_meetup

        if is_conference:
            conference_talks += 1
        elif is_meetup:
            meetup_talks += 1

        # Check if talk has recording (contains markdown link)
        has_recording = bool(re.search(r"\[.*?\]\(.*?\)", talk_column))

        if has_recording:
            talks_with_recordings += 1
            if is_conference:
                conferences_with_recordings += 1
            elif is_meetup:
                meetups_with_recordings += 1

    return (
        total_talks,
        talks_with_recordings,
        conference_talks,
        meetup_talks,
        conferences_with_recordings,
        meetups_with_recordings,
        countries_by_year,
        talks_by_year,
    )


def format_countries_with_flags(countries):
    """Format a set of countries (as emoji flags) with their names."""
    result = []
    for flag in sorted(countries):
        name = flag_to_country(flag) or flag
        result.append(f"{flag} {name}")
    return ", ".join(result)


def format_flags_only(countries):
    """Format a set of countries as emoji flags only (no names)."""
    return " ".join(sorted(countries))


def format_talks_as_emojis(talks):
    """Format a list of (month, location_type, country_flag) talks as emojis in chronological order.

    Uses flag emoji for in-person talks and 📺 for online/YouTube talks.
    """
    # Sort by month to ensure chronological order
    sorted_talks = sorted(talks, key=lambda x: x[0])
    emojis = []
    for _, location_type, country_flag in sorted_talks:
        if location_type != LOCATION_COUNTRY:
            emojis.append("📺")
        else:
            emojis.append(country_flag if country_flag else "❓")
    return " ".join(emojis)


def format_talks_as_html(talks):
    """Format a list of (month, location_type, country_flag) talks as HTML with logos/flags."""
    # Sort by month to ensure chronological order
    sorted_talks = sorted(talks, key=lambda x: x[0])
    html_parts = []
    for _, location_type, country_flag in sorted_talks:
        if location_type == LOCATION_YOUTUBE:
            html_parts.append(
                '<img src="https://www.youtube.com/favicon.ico" alt="YouTube" '
                'class="icon" title="YouTube">'
            )
        elif location_type == LOCATION_ONLINE:
            html_parts.append(
                '<img src="https://st1.zoom.us/zoom.ico" alt="Zoom" '
                'class="icon" title="Online (Zoom)">'
            )
        else:
            country_name = flag_to_country(country_flag) or country_flag
            html_parts.append(
                f'<span class="flag" title="{country_name}">{country_flag if country_flag else "❓"}</span>'
            )
    return "".join(html_parts)


def generate_html(stats):
    """Generate an HTML page with the statistics."""
    (
        total_talks,
        talks_with_recordings,
        conference_talks,
        meetup_talks,
        conferences_with_recordings,
        meetups_with_recordings,
        countries_by_year,
        talks_by_year,
    ) = stats

    all_countries = set()
    for countries in countries_by_year.values():
        all_countries.update(countries)

    # Build countries by year HTML
    countries_by_year_html = ""
    for year in sorted(countries_by_year.keys()):
        country_flags = countries_by_year[year]
        flags = "".join(
            f'<span class="flag" title="{flag_to_country(f) or f}">{f}</span>'
            for f in sorted(country_flags)
        )
        countries_by_year_html += f'<div class="year-row"><span class="year">{year}</span> <span class="count">({len(country_flags)})</span> <span class="flags">{flags}</span></div>\n'

    # Build talks by year HTML
    talks_by_year_html = ""
    for year in sorted(talks_by_year.keys()):
        talks = talks_by_year[year]
        talks_html = format_talks_as_html(talks)
        talks_by_year_html += f'<div class="year-row"><span class="year">{year}</span> <span class="count">({len(talks)})</span> <span class="flags">{talks_html}</span></div>\n'

    # All countries as flags only
    all_countries_html = " ".join(
        f'<span class="flag" title="{flag_to_country(f) or f}">{f}</span>'
        for f in sorted(all_countries)
    )

    meetup_percentage = (
        f"{meetups_with_recordings/meetup_talks*100:.1f}%"
        if meetup_talks > 0
        else "N/A"
    )

    html = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Conference Talks Statistics</title>
    <style>
        * {{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }}
        
        body {{
            font-family: 'SF Mono', 'Fira Code', 'Consolas', 'Monaco', monospace;
            background: #0d0d0d;
            min-height: 100vh;
            color: #c0c0c0;
            padding: 3rem 4.5rem;
            font-size: 1.5rem;
        }}
        
        .container {{
            max-width: 1200px;
            margin: 0 auto;
        }}
        
        h1 {{
            font-size: 2.1rem;
            font-weight: normal;
            margin-bottom: 3rem;
            color: #808080;
        }}
        
        .row {{
            display: flex;
            gap: 6rem;
            margin-bottom: 3rem;
            flex-wrap: wrap;
        }}
        
        .section {{
            margin-bottom: 2.25rem;
        }}
        
        .section-inline {{
            display: flex;
            align-items: baseline;
            gap: 1.5rem;
            flex-wrap: wrap;
        }}
        
        h2 {{
            font-size: 1.5rem;
            font-weight: normal;
            color: #5a5a5a;
            margin-bottom: 1.125rem;
        }}
        
        h2::before {{
            content: "# ";
            color: #3a3a3a;
        }}
        
        .stats {{
            display: flex;
            gap: 3rem;
            flex-wrap: wrap;
        }}
        
        .stat {{
            display: flex;
            gap: 0.75rem;
        }}
        
        .stat-label {{
            color: #5a5a5a;
        }}
        
        .stat-label::after {{
            content: ":";
        }}
        
        .stat-value {{
            color: #4ec9b0;
        }}
        
        .year-row {{
            display: flex;
            align-items: center;
            gap: 1.125rem;
            margin-bottom: 0.75rem;
        }}
        
        .year {{
            color: #569cd6;
            min-width: 75px;
        }}
        
        .count {{
            color: #5a5a5a;
            min-width: 53px;
        }}
        
        .flags {{
            display: flex;
            gap: 6px;
            flex-wrap: wrap;
            align-items: center;
        }}
        
        .flag {{
            font-size: 1.875rem;
            cursor: default;
        }}
        
        .icon {{
            width: 30px;
            height: 30px;
            vertical-align: middle;
        }}
        
        .countries-list {{
            line-height: 2.5;
            color: #c0c0c0;
        }}
        
        .legend {{
            display: flex;
            gap: 3rem;
            margin-top: 1.5rem;
            color: #5a5a5a;
            font-size: 1.275rem;
        }}
        
        .legend-item {{
            display: flex;
            align-items: center;
            gap: 0.6rem;
        }}

        .divider {{
            border: none;
            border-top: 1px solid #2a2a2a;
            margin: 2.25rem 0;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>Conference Talks Statistics</h1>
        
        <div class="section">
            <h2>overall</h2>
            <div class="stats">
                <div class="stat"><span class="stat-label">total</span> <span class="stat-value">{total_talks}</span></div>
                <div class="stat"><span class="stat-label">recorded</span> <span class="stat-value">{talks_with_recordings}</span></div>
                <div class="stat"><span class="stat-label">unrecorded</span> <span class="stat-value">{total_talks - talks_with_recordings}</span></div>
                <div class="stat"><span class="stat-label">recording %</span> <span class="stat-value">{talks_with_recordings/total_talks*100:.1f}%</span></div>
            </div>
            <div class="stats" style="margin-top: 0.75rem;">
                <div class="stat"><span class="stat-label">conferences</span> <span class="stat-value">{conference_talks}</span> <span class="stat-label" style="margin-left: 0.75rem">recorded</span> <span class="stat-value">{conferences_with_recordings} ({conferences_with_recordings/conference_talks*100:.0f}%)</span></div>
                <div class="stat"><span class="stat-label">meetups</span> <span class="stat-value">{meetup_talks}</span> <span class="stat-label" style="margin-left: 0.75rem">recorded</span> <span class="stat-value">{meetups_with_recordings} ({meetup_percentage})</span></div>
            </div>
        </div>
        
        <hr class="divider">
        
        <div class="section">
            <h2>all countries ({len(all_countries)})</h2>
            <div class="countries-list">{all_countries_html}</div>
        </div>
        
        <hr class="divider">
        
        <div class="row">
            <div class="section">
                <h2>countries by year</h2>
                {countries_by_year_html}
            </div>
            
            <div class="section" style="flex: 1;">
                <h2>talks by year</h2>
                {talks_by_year_html}
            </div>
        </div>
    </div>
</body>
</html>
"""
    return html


def main():
    """Main function to run the analysis."""
    readme_path = Path("README.md")

    if not readme_path.exists():
        print("Error: README.md not found in current directory")
        sys.exit(1)

    try:
        with open(readme_path, "r", encoding="utf-8") as f:
            content = f.read()

        stats = parse_conference_talks_table(content)
        (
            total_talks,
            talks_with_recordings,
            conference_talks,
            meetup_talks,
            conferences_with_recordings,
            meetups_with_recordings,
            countries_by_year,
            talks_by_year,
        ) = stats

        # Print summary to console
        print("=== Conference Talks Statistics ===")
        print(f"Total talks: {total_talks}")
        print(f"Talks with recordings: {talks_with_recordings}")
        print(f"Recording percentage: {talks_with_recordings/total_talks*100:.1f}%")
        print()

        # Generate and open HTML page
        html_content = generate_html(stats)

        # Write to a temporary HTML file
        with tempfile.NamedTemporaryFile(
            mode="w", suffix=".html", delete=False, encoding="utf-8"
        ) as f:
            f.write(html_content)
            html_path = f.name

        print(f"Opening statistics page: {html_path}")
        webbrowser.open(f"file://{html_path}")

    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
