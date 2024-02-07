#include <stdio.h>

struct Item {
    int quantity;
    float unit_price;
};

float calculation_Item_Cost(struct Item item) {
    return item.quantity * item.unit_price;
}

int main() {
    struct Item paratha, vegetables, mineral_Water;
    int numberOfPeople;

    // Input section -----------------------------
    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &paratha.unit_price);

    printf("Quantity Of Vegetables: ");
    scanf("%d", &vegetables.quantity);
    printf("Unit Price: ");
    scanf("%f", &vegetables.unit_price);

    printf("Quantity Of Mineral Water: ");
    scanf("%d", &mineral_Water.quantity);
    printf("Unit Price: ");
    scanf("%f", &mineral_Water.unit_price);


    printf("Number of People: ");
    scanf("%d", &numberOfPeople);
    // Input section end-----------------------------

    float CostParatha = calculation_Item_Cost(paratha);
    float CostVegetables = calculation_Item_Cost(vegetables);
    float CostMineralWater = calculation_Item_Cost(mineral_Water);
    float totalBill = CostParatha + CostVegetables + CostMineralWater;
    float individualCost = totalBill / numberOfPeople;


    printf("Individual people will pay: %.2f tk\n", individualCost);
    return 0;
}

