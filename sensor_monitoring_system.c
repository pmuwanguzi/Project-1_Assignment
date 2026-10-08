#include <stdio.h>
#include <math.h>   /* this is to help us run the fabs() */


#define IDEAL_TEMPERATURE 25.0f

/* Function prototypes */
float calculateTemperatureDeviation(float temperature);
float calculateTurbidityPenalty(float turbidity);
float calculateIndex(float temperature, float turbidity);
const char *classifyWater(float index);
void printReport(float temperature, float turbidity, float index, const char *status);

int main(void)
{
    /* 1. Sensor reading variables */
    float temperature = 28.5f;   /* degrees Celsius */
    float turbidity   = 12.0f;   /* NTU */

    /* 2. Calculate the water-quality index */
    float index = calculateIndex(temperature, turbidity);

    /* 3. Classify the water */
    const char *status = classifyWater(index);

    /* 4. Print the monitoring report */
    printReport(temperature, turbidity, index, status);

    return 0;
}

/* TemperatureDeviation = |Temperature - 25| */
float calculateTemperatureDeviation(float temperature)
{
    return fabsf(temperature - IDEAL_TEMPERATURE);
}

/* TurbidityPenalty = Turbidity / 2 */
float calculateTurbidityPenalty(float turbidity)
{
    return turbidity / 2.0f;
}

/* Index = 100 - (TemperatureDeviation + TurbidityPenalty) */
float calculateIndex(float temperature, float turbidity)
{
    return 100.0f - (calculateTemperatureDeviation(temperature)
                     + calculateTurbidityPenalty(turbidity));
}

/* Good: >= 80, Warning: 60 to < 80, Critical: < 60 */
const char *classifyWater(float index)
{
    if (index >= 80.0f)
        return "Good";
    else if (index >= 60.0f)
        return "Warning";
    else
        return "Critical";
}

void printReport(float temperature, float turbidity, float index, const char *status)
{
    printf("==========================================\n");
    printf("     WATER-QUALITY MONITORING REPORT\n");
    printf("==========================================\n");
    printf(" Temperature           : %6.2f C\n", temperature);
    printf(" Turbidity             : %6.2f NTU\n", turbidity);
    printf("------------------------------------------\n");
    printf(" Temperature Deviation : %6.2f\n", calculateTemperatureDeviation(temperature));
    printf(" Turbidity Penalty     : %6.2f\n", calculateTurbidityPenalty(turbidity));
    printf(" Water-Quality Index   : %6.2f\n", index);
    printf("------------------------------------------\n");
    printf(" Status                : %s\n", status);
    printf("==========================================\n");
}
