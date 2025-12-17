#!/usr/bin/env python3
"""
Script to analyze talk statistics from README.md
Counts total talks and talks with recordings from the Conference Talks table.
Also tracks countries visited by year.
"""

import re
import sys
from pathlib import Path
from collections import defaultdict

# Map country names to ISO 3166-1 alpha-2 codes for flag emojis
COUNTRY_TO_ISO = {
    "USA": "US",
    "UK": "GB",
    "Germany": "DE",
    "Poland": "PL",
    "Canada": "CA",
    "Hungary": "HU",
    "Norway": "NO",
    "Spain": "ES",
    "Netherlands": "NL",
    "Denmark": "DK",
    "Australia": "AU",
    "Italy": "IT",
}


def country_to_flag(country):
    """Convert a country name to its flag emoji."""
    iso_code = COUNTRY_TO_ISO.get(country, "")
    if not iso_code:
        return ""
    # Convert ISO code to regional indicator symbols (flag emoji)
    return "".join(chr(0x1F1E6 + ord(c) - ord("A")) for c in iso_code)


def extract_country(location):
    """Extract country from location string like 'Santa Clara, USA' or 'Australia'."""
    if not location or location.lower() in ("online", "youtube"):
        return None

    # If there's a comma, take the part after the last comma
    if "," in location:
        return location.split(",")[-1].strip()
    # Otherwise the whole string is likely the country
    return location.strip()


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
            # Look for the table header
            for j in range(i, min(i + 10, len(lines))):
                if "|Conference/Meetup|Year|Location|Talk|" in lines[j]:
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
        is_online = location_col.lower() in ("online", "youtube")
        talks_by_year[year].append((month, country if not is_online else None))

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
    """Format a set of countries with their flag emojis and names."""
    return ", ".join(f"{country_to_flag(c)} {c}" for c in sorted(countries))


def format_flags_only(countries):
    """Format a set of countries as emoji flags only (no names)."""
    return " ".join(country_to_flag(c) for c in sorted(countries))


def format_talks_as_emojis(talks):
    """Format a list of (month, country) talks as emojis in chronological order.

    Uses flag emoji for in-person talks and 📺 for online/YouTube talks.
    """
    # Sort by month to ensure chronological order
    sorted_talks = sorted(talks, key=lambda x: x[0])
    emojis = []
    for _, country in sorted_talks:
        if country is None:
            emojis.append("📺")
        else:
            flag = country_to_flag(country)
            emojis.append(flag if flag else "❓")
    return " ".join(emojis)


def main():
    """Main function to run the analysis."""
    readme_path = Path("README.md")

    if not readme_path.exists():
        print("Error: README.md not found in current directory")
        sys.exit(1)

    try:
        with open(readme_path, "r", encoding="utf-8") as f:
            content = f.read()

        (
            total_talks,
            talks_with_recordings,
            conference_talks,
            meetup_talks,
            conferences_with_recordings,
            meetups_with_recordings,
            countries_by_year,
            talks_by_year,
        ) = parse_conference_talks_table(content)

        print("=== Conference Talks Statistics ===")
        print(f"Total talks: {total_talks}")
        print(f"Talks with recordings: {talks_with_recordings}")
        print(f"Talks without recordings: {total_talks - talks_with_recordings}")
        print(f"Recording percentage: {talks_with_recordings/total_talks*100:.1f}%")
        print()

        print("=== Breakdown by Type ===")
        print(f"Conference talks: {conference_talks}")
        print(f"Conference talks with recordings: {conferences_with_recordings}")
        print(
            f"Conference recording percentage: {conferences_with_recordings/conference_talks*100:.1f}%"
        )
        print()

        print(f"Meetup talks: {meetup_talks}")
        print(f"Meetup talks with recordings: {meetups_with_recordings}")
        if meetup_talks > 0:
            print(
                f"Meetup recording percentage: {meetups_with_recordings/meetup_talks*100:.1f}%"
            )
        else:
            print("Meetup recording percentage: N/A")
        print()

        # Country statistics
        all_countries = set()
        for countries in countries_by_year.values():
            all_countries.update(countries)

        print("=== Countries Visited ===")
        print(f"Total countries: {len(all_countries)}")
        print(f"Countries: {format_countries_with_flags(all_countries)}")
        print()

        print("=== Countries by Year ===")
        for year in sorted(countries_by_year.keys()):
            countries = countries_by_year[year]
            print(f"{year}: ({len(countries)}) {format_flags_only(countries)}")
        print()

        print("=== Talks by Year ===")
        for year in sorted(talks_by_year.keys()):
            talks = talks_by_year[year]
            print(f"{year}: ({len(talks)}) {format_talks_as_emojis(talks)}")

    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
