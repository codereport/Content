#!/usr/bin/env python3
"""
Script to analyze talk statistics from README.md
Counts total talks and talks with recordings from the Conference Talks table.
"""

import re
import sys
from pathlib import Path


def parse_conference_talks_table(readme_content):
    """
    Parse the Conference Talks markdown table and extract statistics.
    
    Returns:
        tuple: (total_talks, talks_with_recordings, conference_talks, meetup_talks, 
                conferences_with_recordings, meetups_with_recordings)
    """
    lines = readme_content.split('\n')

    # Find the Conference Talks table
    table_start = None
    table_end = None

    for i, line in enumerate(lines):
        if '## Conference Talks' in line:
            # Look for the table header
            for j in range(i, min(i + 10, len(lines))):
                if '|Conference/Meetup|Year|Location|Talk|' in lines[j]:
                    table_start = j + 2  # Skip header and separator
                    break
            break

    if table_start is None:
        raise ValueError("Could not find Conference Talks table")

    # Find where the table ends (next section or empty line)
    for i in range(table_start, len(lines)):
        line = lines[i].strip()
        if not line or not line.startswith('|') or line.startswith(
                '1 -') or line.startswith('\\*'):
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

    for i in range(table_start, table_end):
        line = lines[i].strip()
        if not line or not line.startswith('|'):
            continue

        # Split the table row
        columns = [col.strip() for col in line.split('|')[1:-1]
                   ]  # Remove empty first/last elements

        if len(columns) < 4:
            continue

        conference_meetup = columns[0]
        talk_column = columns[3]

        # Count total talks
        total_talks += 1

        # Check if it's a conference or meetup
        is_conference = ':green_heart:' in conference_meetup
        is_meetup = ':blue_heart:' in conference_meetup

        if is_conference:
            conference_talks += 1
        elif is_meetup:
            meetup_talks += 1

        # Check if talk has recording (contains markdown link)
        has_recording = bool(re.search(r'\[.*?\]\(.*?\)', talk_column))

        if has_recording:
            talks_with_recordings += 1
            if is_conference:
                conferences_with_recordings += 1
            elif is_meetup:
                meetups_with_recordings += 1

    return (total_talks, talks_with_recordings, conference_talks, meetup_talks,
            conferences_with_recordings, meetups_with_recordings)


def main():
    """Main function to run the analysis."""
    readme_path = Path('README.md')

    if not readme_path.exists():
        print("Error: README.md not found in current directory")
        sys.exit(1)

    try:
        with open(readme_path, 'r', encoding='utf-8') as f:
            content = f.read()

        (total_talks, talks_with_recordings, conference_talks, meetup_talks,
         conferences_with_recordings,
         meetups_with_recordings) = parse_conference_talks_table(content)

        print("=== Conference Talks Statistics ===")
        print(f"Total talks: {total_talks}")
        print(f"Talks with recordings: {talks_with_recordings}")
        print(
            f"Talks without recordings: {total_talks - talks_with_recordings}")
        print(
            f"Recording percentage: {talks_with_recordings/total_talks*100:.1f}%"
        )
        print()

        print("=== Breakdown by Type ===")
        print(f"Conference talks: {conference_talks}")
        print(
            f"Conference talks with recordings: {conferences_with_recordings}")
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

    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == '__main__':
    main()
