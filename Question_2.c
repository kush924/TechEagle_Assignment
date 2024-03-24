#include <stdio.h>
#include <math.h>
#define step_size_deg 0.1
#define pi 3.14159265
#define root3 1.73205080

int main()
{
    double x = 0, y = 0, r = 1, q_deg = 0, qf_deg = 90; //
    double q_rad = q_deg * (pi / 180.0);
    double qf_rad = qf_deg * (pi / 180.0);
    double step_size_rad = step_size_deg * (pi / 180.0);

    x = r * cos(q_rad);
    y = r * sin(q_rad);

    FILE *fptr = fopen("data.txt", "w");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    fprintf(fptr, "%f,%f\n", x, y);

    while (q_rad < qf_rad)
    {
        q_rad += step_size_rad;
        double x2 = r * cos(q_rad);
        double y2 = y + (x2 - x) * tan((-root3 * x + y) / (x + root3 * y));
        y = y2;x = x2;
        r = sqrt(x * x + y * y);
        fprintf(fptr, "%f,%f\n", x, y);
    }

    fclose(fptr);

    return 0;
}

// tan((-root3 * x + y) / (x + root3 * y))
// tan(tan(120 * (pi / 180.0) + q_rad))