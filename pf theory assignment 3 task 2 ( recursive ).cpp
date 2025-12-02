#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {

    
    if (fuel <= 0) {
        printf("Planet %d: Fuel Remaining = 0\n", planet);
        printf(" Mission failed Spacecraft ran out of fuel.\n");
        return;
    }

   
    if (planet > totalPlanets) {
        printf(" Mission successful Spacecraft completed the journey.\n");
        return;
    }

    
    fuel = fuel - consumption;   
    fuel = fuel + recharge;      

   
    if (planet % 4 == 0) {
        fuel += solarBonus;
    }

    
    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

   
    calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int fuel = 100;
    int consumption = 10;
    int recharge = 5;
    int solarBonus = 20;
    int totalPlanets = 6;

    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);

    return 0;
}
