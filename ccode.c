// code 1 

if ((a > b && c < d) || (x == y && p != q)) {
    if ((m >= n && u < v) || !(k == t)) {
        printf("Condition 1\n");
    } else if ((r + s > t) && (w <= z || h != j)) {
        printf("Condition 2\n");
    } else {
        printf("Condition 3\n");
    }
}
else if ((a == b || c >= d) && (x != y || p < q)) {
    if ((m < n && u >= v) || (k != t && h > j)) {
        printf("Condition 4\n");
    } else if (!(r < s) && (t >= w || z == 0)) {
        printf("Condition 5\n");
    } else {
        printf("Condition 6\n");
    }
}
else if ((a + b > c) && (d - e < f) && ((g == h) || (i != j && k > l))) {
    printf("Condition 7\n");
}
else {
    if ((m * n > p) || (q / 2 < r && s != t)) {
        printf("Condition 8\n");
    } else {
        printf("Condition 9\n");
    }
}

// code 2

for (i = 1; i <= SUBJECT_COUNT; i++) {
    if (i == 1) {
        mark1 = mark1 + BONUS;
        total = total + mark1;
    } else if (i == 2) {
        mark2 = mark2 + BONUS;
        total = total + mark2;
    } else {
        mark3 = mark3 + BONUS;
        total = total + mark3;
    }
}

// code 3

float calculateAverage(int total, int count) {
    return (float) total / count;   // type casting
}