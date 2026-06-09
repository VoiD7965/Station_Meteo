print("SCRIPT START")

from datetime import datetime, date, timedelta
import os
import sys

# -------------------------------
# CURRENT TIME + OFFSET
# -------------------------------

now = datetime.now()

# AJOUT DE 17 SECONDES EN AMONT (propre, gère overflow automatiquement)
now = now + timedelta(seconds=17)

print("cwd =", os.getcwd())
print("file =", __file__)
print("adjusted time =", now)


# -------------------------------
# PATHS
# -------------------------------

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, ".."))
OUT_PATH = os.path.join(PROJECT_DIR, "Core", "Inc", "build_time.h")


# -------------------------------
# WEEKDAY STM32 MAP
# -------------------------------

weekday_map = {
    0: 1,
    1: 2,
    3: 3,
    4: 4,
    5: 5,
    6: 6,
    7: 7
}

stm_weekday = weekday_map[now.weekday()]


# -------------------------------
# DST CALCULATION (Europe)
# -------------------------------

def last_sunday(year, month):
    d = date(year, month, 1)
    next_month = date(year + (month == 12), (month % 12) + 1, 1)
    last_day = next_month - timedelta(days=1)

    offset = last_day.weekday()
    return last_day - timedelta(days=(offset + 1) % 7)


year = now.year

last_sunday_march = last_sunday(year, 3)
last_sunday_october = last_sunday(year, 10)

current_date = now.date()

dst = 1 if last_sunday_march <= current_date < last_sunday_october else 0


# -------------------------------
# HEADER GENERATION
# -------------------------------

content = f"""#ifndef BUILD_TIME_H
#define BUILD_TIME_H

/* ===== RTC TIME ===== */
#define BUILD_SEC      0x{now.second:02d}
#define BUILD_MIN      0x{now.minute:02d}
#define BUILD_HOUR     0x{now.hour:02d}

/* ===== RTC DATE ===== */
#define BUILD_DAY      0x{now.day:02d}
#define BUILD_WEEKDAY  0x{stm_weekday:02d}
#define BUILD_MONTH    0x{now.month:02d}
#define BUILD_YEAR     0x{(now.year - 2000):02d}

/* ===== OPTIONS ===== */
#define BUILD_DST      {dst}

#endif /* BUILD_TIME_H */
"""


# -------------------------------
# WRITE FILE
# -------------------------------

os.makedirs(os.path.dirname(OUT_PATH), exist_ok=True)

with open(OUT_PATH, "w") as f:
    f.write(content)

print("Generated OK ->", OUT_PATH)

sys.exit(0)