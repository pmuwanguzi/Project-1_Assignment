#include <stdio.h>

#define MAX_ROUTES 100

/* ---------- Function prototypes ---------- */
void   readDistances(int distances[], int n);
int    calculateTotal(const int distances[], int n);
double calculateAverage(const int distances[], int n);
int    findLongest(const int distances[], int n);
int    countAboveLimit(const int distances[], int n, int limit);
int    recursiveSum(const int distances[], int n);
void   displayResults(int total, double average, int longest,
                      int limit, int countAbove, int recSum);

/* ---------- Main ---------- */
int main(void)
{
    int distances[MAX_ROUTES];
    int n, limit;

    /* Read and validate the number of routes */
    printf("Enter number of routes (1-%d): ", MAX_ROUTES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_ROUTES) {
        printf("Invalid number of routes.\n");
        return 1;
    }

    readDistances(distances, n);

    printf("Enter distance limit (km): ");
    if (scanf("%d", &limit) != 1) {
        printf("Invalid limit.\n");
        return 1;
    }

    /* Call each analysis function */
    int    total      = calculateTotal(distances, n);
    double average    = calculateAverage(distances, n);   /* reuses calculateTotal() */
    int    longest    = findLongest(distances, n);
    int    countAbove = countAboveLimit(distances, n, limit);
    int    recSum     = recursiveSum(distances, n);

    displayResults(total, average, longest, limit, countAbove, recSum);

    /* Function reuse: same function called again with different arguments */
    printf("\n----- Function Reuse Demonstration -----\n");
    printf("Routes above %d km (half the limit): %d\n",
           limit / 2, countAboveLimit(distances, n, limit / 2));
    printf("Routes above average (%.2f km): %d\n",
           average, countAboveLimit(distances, n, (int)average));
    if (n >= 3) {
        printf("Total of first 3 routes (recursive): %d km\n",
               recursiveSum(distances, 3));
    }

    /* Verification: iterative and recursive results should match */
    printf("Iterative and recursive sums %s.\n",
           (total == recSum) ? "MATCH" : "DO NOT MATCH");

    return 0;
}

/* Reads n distances from the user into the array, rejecting negatives */
void readDistances(int distances[], int n)
{
    printf("Enter %d distances (km): ", n);
    for (int i = 0; i < n; i++) {
        while (scanf("%d", &distances[i]) != 1 || distances[i] < 0) {
            printf("Invalid distance. Re-enter distance %d: ", i + 1);
            while (getchar() != '\n')   /* clear bad input */
                ;
        }
    }
}

/* Returns the sum of all distances using a loop (iterative) */
int calculateTotal(const int distances[], int n)
{
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += distances[i];
    }
    return total;
}

/* Returns the average distance; reuses calculateTotal() */
double calculateAverage(const int distances[], int n)
{
    if (n == 0) {
        return 0.0;
    }
    return (double)calculateTotal(distances, n) / n;
}

/* Returns the largest distance in the array */
int findLongest(const int distances[], int n)
{
    int longest = distances[0];
    for (int i = 1; i < n; i++) {
        if (distances[i] > longest) {
            longest = distances[i];
        }
    }
    return longest;
}

/* Returns how many distances are strictly greater than limit */
int countAboveLimit(const int distances[], int n, int limit)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (distances[i] > limit) {
            count++;
        }
    }
    return count;
}

/*
 * Recursive sum:
 *   Base case:      n == 0  -> an empty array sums to 0
 *   Recursive case: sum of first n elements =
 *                   distances[n-1] + sum of first (n-1) elements
 * Each call reduces n by 1, so it always reaches the base case.
 */
int recursiveSum(const int distances[], int n)
{
    if (n == 0) {
        return 0;                                            /* base case */
    }
    return distances[n - 1] + recursiveSum(distances, n - 1); /* recursive case */
}

/* Prints all results in a clear report format */
void displayResults(int total, double average, int longest,
                    int limit, int countAbove, int recSum)
{
    printf("\n===== DELIVERY DISTANCE ANALYSIS =====\n");
    printf("Total distance: %d km\n", total);
    printf("Average distance: %.2f km\n", average);
    printf("Longest route: %d km\n", longest);
    printf("Routes above %d km: %d\n", limit, countAbove);
    printf("Recursive sum: %d km\n", recSum);
}
