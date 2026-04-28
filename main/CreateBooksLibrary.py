import random
import itertools

# ── CONTROL PARAMETER ─────────────────────────────────────────────────────────
NUM_BOOKS   = 5000        # <-- change this to control the number of books
MIN_COPIES  = 1           # minimum copies per book
MAX_COPIES  = 6           # maximum copies per book
OUTPUT_FILE = "library.txt"
RANDOM_SEED = 42          # set to None for fully random output
# ─────────────────────────────────────────────────────────────────────────────

STATUSES       = ["available", "borrowed", "damaged"]
STATUS_WEIGHTS = [0.60, 0.30, 0.10]   # probability weights per status

# ── TITLE VOCABULARY ──────────────────────────────────────────────────────────
PREFIXES = [
    "Introduction to",
    "Advanced",
    "Applied",
    "Foundations of",
    "Principles of",
    "Fundamentals of",
    "Elements of",
    "Theory of",
    "Modern",
    "Classical",
    "Practical",
    "A Practical Guide to",
    "Analysis and Design of",
    "Understanding",
    "Mastering",
    "Essential",
    "Core Concepts in",
    "Topics in",
    "A Critical Approach to",
    "Handbook of",
    "Survey of",
    "Concepts in",
]

SUBJECTS = [
    "Algorithms",
    "Data Structures",
    "Database Systems",
    "Operating Systems",
    "Computer Networks",
    "Artificial Intelligence",
    "Machine Learning",
    "Deep Learning",
    "Cryptography",
    "Cybersecurity",
    "Parallel Computing",
    "Distributed Systems",
    "Computational Theory",
    "Programming Languages",
    "Compiler Design",
    "Software Engineering",
    "Computer Graphics",
    "Human-Computer Interaction",
    "Computational Geometry",
    "Graph Theory",
    "Information Systems",
    "Digital Signal Processing",
    "Numerical Analysis",
    "Computer Science",
    "Robotics",
    "Computational Biology",
    "Digital Circuits",
    "Computer Architecture",
    "Embedded Systems",
    "Computer Vision",
    "Natural Language Processing",
    "Quantum Computing",
    "Cloud Computing",
    "Network Security",
    "Software Testing",
]

SUFFIXES = [
    "",    # no suffix — listed three times to increase plain-title frequency
    "",
    "",
    ": Theory and Practice",
    ": Principles and Applications",
    ": Methods and Applications",
    ": From Theory to Practice",
    ": Modern Approaches",
    ": Concepts and Algorithms",
    ": A Practical Approach",
    ": Techniques and Tools",
    ": Advanced Techniques",
    "for Programmers",
    "for Software Engineers",
    "for Data Scientists",
    ": A Complete Guide",
    ": An Algorithmic Perspective",
    ": Analysis and Implementation",
]

# ── AUTHOR VOCABULARY ─────────────────────────────────────────────────────────
LAST_NAMES = [
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Miller", "Davis",
    "Wilson", "Moore", "Taylor", "Anderson", "Thomas", "Jackson", "White",
    "Harris", "Martin", "Thompson", "Garcia", "Martinez", "Robinson",
    "Clark", "Lewis", "Lee", "Walker", "Hall", "Allen", "Young", "King",
    "Wright", "Hill", "Scott", "Green", "Adams", "Baker", "Nelson",
    "Carter", "Mitchell", "Perez", "Roberts", "Turner", "Phillips",
    "Campbell", "Parker", "Evans", "Edwards", "Collins", "Stewart",
    "Knuth", "Cormen", "Tanenbaum", "Sedgewick", "Sipser", "Russell",
    "Norvig", "Goodfellow", "Bishop", "Hopcroft", "Ullman", "Aho",
    "Patterson", "Hennessy", "Silberschatz", "Galvin", "Lamport",
]

FIRST_INITIALS = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")


# ── ISBN-13 ───────────────────────────────────────────────────────────────────
def isbn13_check_digit(digits_12: str) -> str:
    """Computes the check digit of an ISBN-13 from its first 12 digits."""
    total = sum(
        int(d) * (1 if i % 2 == 0 else 3)
        for i, d in enumerate(digits_12)
    )
    return str((10 - (total % 10)) % 10)


def make_isbn(rng: random.Random) -> str:
    """Generates a valid synthetic ISBN-13 in the format 978-xxx-xx-xxxx-x."""
    group   = str(rng.randint(0, 999)).zfill(3)
    pub     = str(rng.randint(0, 99)).zfill(2)
    title_n = str(rng.randint(0, 9999)).zfill(4)
    base    = f"978{group}{pub}{title_n}"
    check   = isbn13_check_digit(base)
    return f"978-{group}-{pub}-{title_n}-{check}"


# ── UNIQUE TITLE GENERATION ───────────────────────────────────────────────────
def all_possible_titles():
    """Generator yielding every possible title (PREFIX x SUBJECT x SUFFIX)."""
    for prefix, subject, suffix in itertools.product(PREFIXES, SUBJECTS, SUFFIXES):
        yield f"{prefix} {subject}{suffix}".strip()


def generate_unique_titles(n: int, rng: random.Random) -> list:
    """
    Returns a list of n unique titles sampled from the full title pool.
    Raises ValueError if n exceeds the number of available unique titles.
    """
    pool = list(set(all_possible_titles()))
    if n > len(pool):
        raise ValueError(
            f"Requested {n} books but only {len(pool)} unique titles can be "
            f"generated. Reduce NUM_BOOKS or extend the vocabulary lists."
        )
    rng.shuffle(pool)
    return pool[:n]


# ── UNIQUE ISBN GENERATION ────────────────────────────────────────────────────
def generate_unique_isbns(n: int, rng: random.Random) -> list:
    isbns = set()
    while len(isbns) < n:
        isbns.add(make_isbn(rng))
    return list(isbns)


# ── AUTHOR ────────────────────────────────────────────────────────────────────
def make_author(rng: random.Random) -> str:
    return f"{rng.choice(LAST_NAMES)} {rng.choice(FIRST_INITIALS)}."


# ── COPIES ────────────────────────────────────────────────────────────────────
def make_copies(rng: random.Random) -> list:
    """Returns a shuffled list of (copyId, status) tuples; at least one copy guaranteed."""
    n = rng.randint(MIN_COPIES, MAX_COPIES)
    copies = [
        (cid, rng.choices(STATUSES, weights=STATUS_WEIGHTS, k=1)[0])
        for cid in range(1, n + 1)
    ]
    rng.shuffle(copies)
    return copies


# ── MAIN ──────────────────────────────────────────────────────────────────────
def main():
    rng = random.Random(RANDOM_SEED)

    print(f"Generating {NUM_BOOKS} books...")

    titles = generate_unique_titles(NUM_BOOKS, rng)
    isbns  = generate_unique_isbns(NUM_BOOKS, rng)

    lines = []
    total_copies  = 0
    status_counts = {s: 0 for s in STATUSES}

    for i in range(NUM_BOOKS):
        author = make_author(rng)
        copies = make_copies(rng)
        total_copies += len(copies)

        lines.append(f"BOOK|{isbns[i]}|{titles[i]}|{author}")
        for copy_id, status in copies:
            lines.append(f"COPY|{copy_id}|{status}")
            status_counts[status] += 1

    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")

    max_possible = len(set(all_possible_titles()))

    print(f"Done! File '{OUTPUT_FILE}' created successfully.")
    print(f"  Books generated    : {NUM_BOOKS}")
    print(f"  Max possible titles: {max_possible}")
    print(f"  Total copies       : {total_copies}")
    print(f"  Avg copies/book    : {total_copies / NUM_BOOKS:.1f}")
    print(f"  Copy status breakdown:")
    for status, count in status_counts.items():
        pct = count / total_copies * 100
        print(f"    {status:<12}: {count:>5}  ({pct:.1f}%)")


if __name__ == "__main__":
    main()
