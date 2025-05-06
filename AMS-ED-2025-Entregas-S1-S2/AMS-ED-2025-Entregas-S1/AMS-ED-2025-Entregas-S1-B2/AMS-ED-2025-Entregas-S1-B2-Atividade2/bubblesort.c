#include <stdio.h>

int main() {
    int n, i, j, temp;

    printf("Digite a quantidade de elementos: ");
    scanf("%d", &n);

    int arr[n];

    for (i = 0; i < n; i++) {
        printf("Digite o elemento %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("\nArray ordenado em ordem crescente:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return 0;
}
