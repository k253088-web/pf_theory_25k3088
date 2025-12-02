// Online C compiler to run C program online
#include <stdio.h>
#include<string.h>

struct Employee{
    int employee_id;
    char name[20];
    char designation[10];
    int salary;
    
};

struct Employee em[2];

void giveBonus(struct Employee em[], int size){
    int h;
    int p;
    int bonus;
    int new_salary;
    for(h=0;h<2;h++){
         if(em[h].salary<50000){
            bonus =em[h].salary*0.1;
            new_salary=em[h].salary+bonus;
            em[h].salary = new_salary;
        
        }
   }
   for(p=0;p<2;p++){
        printf("id: %d\n",em[p].employee_id);
        printf("name: %s\n",em[p].name);
        printf("designation: %s\n",em[p].designation);
        printf("salary: %d\n",em[p].salary);
        printf("\n");
   }
}

void searchEmployee(int id , char name[]){
    int c;
    printf("The person you are searching is:\n");
    for(c=0;c<2;c++){
        if(id==em[c].employee_id || strcmp(name,em[c].name)==0){
               printf("id:%d\n",em[c].employee_id);
               printf("name: %s\n",em[c].name);
               printf("designation: %s\n",em[c].designation);
               printf("salary: %d\n",em[c].salary);
        
        }
    }
}

void displayEmployees(){
     int k;
     
     for(k=0;k<2;k++){
        printf("id: %d\n",em[k].employee_id);
        printf("name: %s\n",em[k].name);
        printf("designation: %s\n",em[k].designation);
        printf("salary: %d\n",em[k].salary);
        printf("\n");
       
    }
    
}

void findHighestSalary(){
    int a;
    int b=0;

    int max=em[0].salary;
    for(a=1;a<2;a++){
        if(em[a].salary>max){
            max=em[a].salary;
            b=a;
        }
    }
   // int b=a;
    printf("maximum salary employee is:\n");
    printf("id: %d\n", em[b].employee_id);
    printf("name: %s\n",em[b].name);
    printf("designation: %s\n",em[b].designation);
    printf("salary: %d\n", max);
    
    //for(;b<2;b++)
   // printf("")
}

int main() {
    
    int i;
    int j=1;
   // int k;
   // printf("enter %d employee all the details of employee in order",j);
    for(i=0;i<2;i++){
        printf("enter %d employee all the details of employee in order\n",j);
        
        printf("enter employee id\n");
        scanf("%d",&em[i].employee_id);
        getchar();
        
        printf("enter employee name\n");
        fgets(em[i].name , sizeof(em[i].name),stdin);
        em[i].name[strcspn(em[i].name,"\n")]= '\0';
        
        printf("enter employee designation\n");
       // scanf("%s",&em[i].designation);
        fgets(em[i].designation , sizeof(em[i].designation),stdin);
        em[i].designation[strcspn(em[i].designation,"\n")]= '\0';
        
        printf("enter salary of employee\n");
        scanf("%d",&em[i].salary);
        getchar(); 
        
        j++;
    }
    
    printf("\n");
    
    int idd;
    char namee[20];
    
    displayEmployees();
    findHighestSalary();
    char ch;
    printf("\nyou want to search a person with id or name? through id press i and if name press n\n");
    scanf("%c",&ch);
    getchar();
if(ch=='i'){
    printf("enter id of the employee you are searching\n");
    scanf("%d",&idd);
    namee[0] = '\0';  
   // getchar();
   searchEmployee( idd , namee);
}
else{
    getchar();
    printf("enter name of the employee you are searching\n");
    //scanf("%s",&namee);
    fgets(namee,sizeof(namee),stdin);
    namee[strcspn(namee, "\n")] = '\0';
     idd = -1;   
     searchEmployee( idd , namee);
}

giveBonus(em, 2);
   // searchEmployee( idd , namee);
    
    //for(k=0;k<2;k++){
      //  printf("id: %d\n",em[k].employee_id);
      //  printf("name: %s\n",em[k].name);
       // printf("designation: %s\n",em[k].designation);
       // printf("salary: %d\n",em[k].salary);
       
   // }
   
    return 0;
}
