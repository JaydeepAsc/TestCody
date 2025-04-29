#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure to represent a JSON object
typedef struct {
    double* values;
    int values_len;
    double* interest_rates;
    int interest_rates_len;
} json_data;

// Function to calculate the cumulative sum
void calculate_cumulative_sum(json_data* data) {
    double* cumulative_sums = (double*)malloc(data->values_len * sizeof(double));
    for (int i = 0; i < data->values_len; i++) {
        cumulative_sums[i] = 0;
        for (int j = 0; j <= i; j++) {
            cumulative_sums[i] += data->values[j] * pow(1 + data->interest_rates[j], i - j);
        }
    }

    // Print the cumulative sums
    printf("{\"cumulative_sums\": [");
    for (int i = 0; i < data->values_len; i++) {
        printf("%f", cumulative_sums[i]);
        if (i < data->values_len - 1) {
            printf(", ");
        }
    }
    printf("]}\n");

    free(cumulative_sums);
}

// Function to parse the JSON data
json_data* parse_json(char* json_str) {
    json_data* data = (json_data*)malloc(sizeof(json_data));
    data->values = NULL;
    data->values_len = 0;
    data->interest_rates = NULL;
    data->interest_rates_len = 0;

    // Parse the JSON string (this is a simplified example and does not handle errors)
    char* token = strtok(json_str, "{");
    token = strtok(NULL, "\"");
    while (token != NULL) {
        if (strcmp(token, "values") == 0) {
            token = strtok(NULL, "[");
            data->values_len = 0;
            while (token != NULL && token[0] != ']') {
                data->values_len++;
                token = strtok(NULL, ",");
            }
            data->values = (double*)malloc(data->values_len * sizeof(double));
            token = strtok(NULL, "[");
            for (int i = 0; i < data->values_len; i++) {
                data->values[i] = atof(token);
                token = strtok(NULL, ",");
            }
        } else if (strcmp(token, "interest_rates") == 0) {
            token = strtok(NULL, "[");
            data->interest_rates_len = 0;
            while (token != NULL && token[0] != ']') {
                data->interest_rates_len++;
                token = strtok(NULL, ",");
            }
            data->interest_rates = (double*)malloc(data->interest_rates_len * sizeof(double));
            token = strtok(NULL, "[");
            for (int i = 0; i < data->interest_rates_len; i++) {
                data->interest_rates[i] = atof(token);
                token = strtok(NULL, ",");
            }
        }
        token = strtok(NULL, "\"");
    }

    return data;
}

int main() {
    char json_str[] = "{\"values\": [100, 200, 300], \"interest_rates\": [0.05, 0.10, 0.15]}";
    json_data* data = parse_json(json_str);
    calculate_cumulative_sum(data);

    free(data->values);
    free(data->interest_rates);
    free(data);

    return 0;
}