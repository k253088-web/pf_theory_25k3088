#include <stdio.h>


float calculateRepayment(float loan, float interestRate, int years) {

    static int year = 1;          
    float installment = 30000;   

    
    if (loan <= 0 || years == 0) {
        return 0;
    }

    
    loan = loan + (loan * interestRate);

    
    float payment = (loan >= installment) ? installment : loan;

   
    loan -= payment;

    
    printf("Year %d: Remaining loan = %.2f\n", year, loan);

    year++; 

   
    float futurePayments = calculateRepayment(loan, interestRate, years - 1);

    return payment + futurePayments;   
}

int main() {

    float loan = 100000;
    float interestRate = 0.05;
    int years = 3;

    float total = calculateRepayment(loan, interestRate, years);

    printf("\nTotal repayment over %d years = %.2f\n", years, total);

    return 0;
}
