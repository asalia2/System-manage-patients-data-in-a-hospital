#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Patient	Name#Gender#Date of	admission#Date  of	birth #Illness#Address(City)#Blood type
 struct node{

    char name[50];
    char gender[1];
    int doa;// date of admission
    int dob;//date of birth
    char illness[50];
    char city[50];
    char blood[2];
    int deleted;// 0: false/ 1: true
    struct node* next;

};
static struct node* head=NULL;
//define functions
int minu();
void read_from_file();
void creat_patient(char namen[50],char gn[1],int doan,int dobn,char illnessn[50],char cityn[50],char bloodn[2]);
void AddNode(struct node** headRef, struct node* newNode);//end of: linked list of patient
int max_length(struct node* head);// to find maximmum length of patients name
void print_all(struct node *head);
struct node* radix_sort(struct node* head);
struct node* copyList(struct node* head);
void delete_List(struct node** head_ref);
void add_new_patient();
struct node* find_patient(struct node* head,char name[50]);
void update(struct node* head);
void delete_patient(struct node* head);
void search_for_name();
void search_for_dob(struct node* head);
void print_Category();
void print_city();
void print_Discharged();
void XML();

int main(){
    int nump,x,choice=1;
    struct node* n;
    printf("\tWelcome in our system \n");

     do{
    choice= minu();
    switch(choice){
        case 1://read data from the file
            read_from_file();
            break;
        case 2://radix sort
            head=radix_sort(head);
            print_all(head);
            break;
         case 3:// add a patient
            add_new_patient();
            printf("=====\n Done!\n");
            break;
         case 4:// update patient's information
           update(head);
            break;
         case 5://To delete patient
             delete_patient(head);
            break;
         case 6://To search for patient //a. Name  b. Date	of	birth
             printf("chose one of option:\n1.to search by patient's name\n2.to search by date of birth\n");
             scanf("%d",&nump);
             switch(nump){
                case 1://search by name
                    search_for_name();
                    break;
                case 2:// search for dob
                    search_for_dob(head);
                    break;
                default:
                      printf("The number you entered dose not exist!!! ");
             }
            break;
         case 7: // To list patient  a. All	patients   b. Category	(i.e.,	illness)  c. City d. Discharged
             printf("chose one of option:\n1.All patients\n2.Category\n3.City\n4.Discharged \n");
             scanf("%d",&x);
             printf("%d",x);
             switch(x){
            case 1:// All patients
                print_all(head);
                break;
            case 2://illness
                print_Category();
                break;
            case 3://City
                 print_city();
                break;
            case 4://Discharged
                print_Discharged();
                break;
            default:
                  printf("The number you entered dose not exist!!! ");
             }
            break;
         case 8://XML format
            XML();
            printf("=====\n Done!\n");
            break;
         case 9:
             printf(" Thank you ...\n");
            break;

         default:
            printf("The number you entered dose not exist!!!\n ");
    }
    }while(choice!=9);

    return 0;
}
void XML(){
    struct node* n=head;
    FILE * fp;
    fp = fopen ("Report.xml","w");
    while(n!=NULL){
            fprintf (fp, "<patient>\n\t<name>%s</name>\n\t<gender>%c</gender>\n\t<admissionDate value=”%d” />\n\t<birthDate value=”%d” />\n",n->name,n->gender[0],n->doa,n->dob);
            fprintf(fp,"\t<diagnosis>%s</diagnosis>\n\t<city>%s</city>\n\t<bloodType>%s</bloodType>\n</patient>\n",n->illness,n->city,n->blood);
            n=n->next;
    }
    fclose (fp);

}

void print_Discharged(){
        struct node *current_node = head;
    if(current_node==NULL)
        printf("The list is Empty!!\n");
    else{
            printf("\n====================================   Discharged Patients   =============================================\n");
            printf("   Name           Gender    Date Of Admission    Date Of Birth   \t Illness  \t    City      Blood\n  ");
            printf("========================================================================================================\n");
        while ( current_node != NULL) {
                if(current_node->deleted!=0)
                printf("  %s \t    %c \t\t%d \t   %d\t  %s \t% s\t %s\n",current_node->name,current_node->gender[0],current_node->doa,current_node->dob,current_node->illness,current_node->city,current_node->blood);
            current_node = current_node->next;
        }
        printf("\n");
    }
}

void print_city(){
    struct node *current_node = head;
    char city[50];
    int count=0;
    if(current_node==NULL)
        printf("The list is Empty!!\n");
    else{
        fflush(stdin);
        printf("Enter the City: ");
        gets(city);
        printf("---------------------------------\n");
        while ( current_node != NULL){
            if (strcasecmp(current_node->city,city)==0&&current_node->deleted==0){
                printf("\nname:%s\n gender:%c\n doa:%d\n dob:%d\n illness:%s\n city:%s\n blood:%s\n****\n",current_node->name,current_node->gender[0],current_node->doa,current_node->dob,current_node->illness,current_node->city,current_node->blood);
                count++;
            }
            current_node = current_node->next;
        }
        if(count==0)
            printf(" The City was not found !\n");
    }
}

void print_Category(){
    struct node *current_node = head;
    char illness[50];
    int count=0;
    if(current_node==NULL)
        printf("The list is Empty!!\n");
    else{
        fflush(stdin);
        printf("Enter the Illness: ");
        gets(illness);
        printf("---------------------------------\n");
        while ( current_node != NULL){
            if (strcasecmp(current_node->illness,illness)==0&&current_node->deleted==0){
                printf("\nname:%s\n gender:%c\n doa:%d\n dob:%d\n illness:%s\n city:%s\n blood:%s\n****\n",current_node->name,current_node->gender[0],current_node->doa,current_node->dob,current_node->illness,current_node->city,current_node->blood);
                count++;
            }
            current_node = current_node->next;
        }
        if(count==0)
            printf(" The illness was not found !\n");
    }
}

void search_for_dob(struct node* head){ //**********
     struct node *current_node = head;
     int dob,count=0;
     if(current_node==NULL)
        printf("The list is Empty!!\n");
     else{
        printf("Enter Date Of Birth: ");
        scanf("%d",&dob);
        printf("---------------------------------\n");

        while ( current_node != NULL){
            if (current_node->dob==dob&&current_node->deleted==0){
                printf("\nname:%s\n gender:%c\n doa:%d\n dob:%d\n illness:%s\n city:%s\n blood:%s\n****\n",current_node->name,current_node->gender[0],current_node->doa,current_node->dob,current_node->illness,current_node->city,current_node->blood);
                count++;
            }
            current_node = current_node->next;
        }
        if(count==0)
            printf(" The patient was not found or deleted!\n");
     }
}

void search_for_name(){ //**********
     struct node *current_node = head;
     char name[50];
    int count=0;// to know if there are patient have this name or not
    if(current_node==NULL)
        printf("The list is Empty!!\n");
    else{
        fflush(stdin);
        printf("Enter Patient's Name: ");
        gets(name);
        printf("---------------------------------\n");
        while ( current_node != NULL){
            if (strcasecmp(current_node->name,name)==0&&current_node->deleted==0){
                printf("\nname:%s\n gender:%c\n doa:%d\n dob:%d\n illness:%s\n city:%s\n blood:%s\n****\n",current_node->name,current_node->gender[0],current_node->doa,current_node->dob,current_node->illness,current_node->city,current_node->blood);
                count++;
            }
            current_node = current_node->next;
        }
        if(count==0)
            printf(" The patient was not found or deleted!\n");
    }
}

void delete_patient(struct node* head){  // 0: false/ 1: true
    char name[50];
    fflush(stdin);
    printf(" Patient's Name: ");
    gets(name);
    struct node* delet=find_patient(head,name);
    if(delet!=NULL&&delet->deleted!=1){
            delet->deleted=1;
            printf("  Done!!\n");
    }
    else
        printf(" The patient was not found or deleted!\n");

}

void update(struct node* head){
    char name[50];
    fflush(stdin);
    printf(" Patient's Name: ");
    gets(name);
    struct node* updat=find_patient(head,name);
    if(updat!=NULL&&updat->deleted!=1){ //if deleted ==1: the patient was deleted
    printf("Date of admission:\n");
    scanf("%d", &updat->doa);
    printf("Date of birth:\n ");
    scanf("%d", &updat->dob);
     fflush(stdin);
     printf("Illness:\n ");
    gets(updat->illness);
    printf("Address (city): ");
    scanf("%s", &updat->city);
    fflush(stdin);
    printf("Blood type:");
    scanf("%s",&updat->blood);
    }
    else
        printf("The patient was not found or deleted!\n");
}

struct node* find_patient(struct node* head,char name[50]){
    struct node *current_node = head;
    if(current_node==NULL)
        printf("The list is Empty!!\n");
    else{
        while ( current_node != NULL&&strcasecmp(current_node->name,name)!=0)
            current_node = current_node->next;
    }
    return current_node;

};

void add_new_patient(){// Patient	Name#Gender#Date of	admission#Date  of	birth #Illness#Address(City)#Blood type
    char name[50],city[50],blood[2],gender[1],illness[50];
    int doa=0,dob=0;

   fflush(stdin);
    printf(" Patient's Name: ");
    gets(name);
    printf("Gender:(F/M) ");
    scanf("%s",&gender);//gender
//    while(gender!='F'&&gender!='f'&&gender!='M'&&gender!='m'){
//            printf("The gender must be (F/M)\nEnter the gender again:\n");
//             scanf("%s", &/*patient->gender*/gender);
//    }
    printf("Date of admission:\n");
    scanf("%d", &doa);
    printf("Date of birth:\n ");
    scanf("%d", &dob);
     fflush(stdin);
     printf("Illness:\n ");
    gets(illness);
    fflush(stdin);
    printf("Address (city): ");
     gets(city);
    fflush(stdin);
    printf("Blood type:");
    gets(blood);
    creat_patient(name,gender,doa,dob,illness,city,blood);
}

struct node* radix_sort(struct node* head){
    struct node* temp,*p,*asci[255],*x,*mov,*newList=NULL;//temp pointer: use to move node from list to asci[i] pointer
    int maxlength=max_length(head),getAscii;

    for(int i=maxlength-1;i>=0;i--){
        for(int j=0;j<=255;j++)
            asci[j]=NULL;

        p=head;
        while(p!=NULL){
            temp=p;
            x=p->next;
            getAscii=(int)(p->name[i]);
            AddNode(&asci[getAscii],temp);
            p=x;
        } struct node* k=NULL;
        for(int j=0;j<=255;j++){
             if(asci[j]!=NULL){
                  mov=asci[j];

                  while(mov!=NULL){
                      k=mov->next;
                      AddNode(&newList,mov);
                    mov=k;
                  }
             }
        }
        head=NULL;
        head=copyList(newList);
        delete_List(&newList);
    }
return head;
}
// Function to create a copy of a linked list
struct node* copyList(struct node* head){
    if (head == NULL) {
        return NULL;
    }
    else {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        strcpy(newNode->name,head->name);
        strcpy(newNode->gender,head->gender);
        newNode->doa=head->doa;
        newNode->dob=head->dob;
        strcpy(newNode->illness,head->illness);
        strcpy(newNode->city,head->city);
        strcpy(newNode->blood,head->blood);
        newNode->deleted=head->deleted;
        //call recursion
        newNode->next = copyList(head->next);
        return newNode;
    }
}
/* Function to delete the entire linked list */
void delete_List(struct node** head_ref){
   struct node* current = *head_ref;
   struct node* next;

   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   /*  real head back */
   *head_ref = NULL;
}
/* Print all the elements in the linked list */
void print_all(struct node *head) {
    struct node *current_node = head;
    if(current_node==NULL)
        printf("The list is Empty!!\n");
    else{
            printf("===================================  List OF Patients  =============================================\n");
            printf("   Name           Gender    Date Of Admission    Date Of Birth   \t Illness  \t    City      Blood\n  ");
            printf("========================================================================================================\n");
        while ( current_node != NULL) {
                if(current_node->deleted==0)
                printf("  %s \t    %c \t\t%d \t   %d\t  %s \t% s\t %s\n",current_node->name,current_node->gender[0],current_node->doa,current_node->dob,current_node->illness,current_node->city,current_node->blood);
            current_node = current_node->next;
        }
    }
}

int minu(){
    int choice=1;
    printf("----------------------------\n");
    printf("1.To read data from the file & create linked list\n");
    printf("2.To sort data\n");
    printf("3.To add a new patient\n");
    printf("4.To update patient's information\n");
    printf("5.To delete patient \n");
    printf("6.To search for patient\n");
    printf("7.To list patient\n");
    printf("8.To export medical report\n");
    printf("9.To Exit \n");
    printf("===================================\n");
    printf("pleas chose one of option \n");
    scanf("%d",&choice);
    printf("\n");
    return choice;
}

void read_from_file(){
     FILE *fop;
    char line[200],blood[2],gender[1],illness[50];
    int doa=0,dob=0;

    fop = fopen("patients.txt", "r");
    if (fop == NULL){
        perror("Error while opening the file.\n");
       return 0;
     }
     while (!feof(fop)){ // Patient	Name#Gender#Date	of	admission#Date	of	birth #Illness#Address	(City)#Blood	type
       char name[50],cit[50];
        fgets(line,200,fop);
        doa=0;doa=0;
        strcpy(name,strtok (line,"#"));
        strcpy(gender,strtok (NULL,"#"));
        doa=atoi(strtok (NULL, "#"));
        dob=atoi(strtok (NULL, "#"));
        strcpy(illness,strtok (NULL, "#"));
        strcpy(cit,strtok (NULL, "#"));
        strcpy(blood,strtok (NULL, "\n"));
        creat_patient(name,gender,doa,dob,illness,cit,blood);
   }
   printf(" Read from file successfully!! \n");
   fclose(fop);
}

void creat_patient(char namen[50],char gn[1],int doan,int dobn,char illnessn[50],char cityn[50],char bloodn[2]){
    struct node* current;
    current=(struct node*)malloc(sizeof( struct node));
    strcpy(current->name,namen);
    strcpy(current->gender,gn);
    //current->gender=gn;
    current->doa=doan;
    current->dob=dobn;
    strcpy(current->illness,illnessn);
    strcpy(current->city,cityn);
    strcpy(current->blood,bloodn);
    current->deleted=0;//by default not deleted

    AddNode(&head,current);
  //  insert_at_end(current);
}

void AddNode(struct node** headRef, struct node* newNode) {
    struct node* current = *headRef;
    newNode->next = NULL;
    // in case length is 0
    if (current == NULL)
        *headRef = newNode;

    else {
        // find the last node
        while (current->next != NULL)
            current = current->next;

        current->next = newNode;
    }
}
// to find maximum length of patients name
int max_length(struct node* head){
    int maxi=0,numb=0;
    struct node* temp=head;
    while(temp!=NULL){
          numb=strlen(temp->name);
          if(numb>maxi)
            maxi=numb;
          temp=temp->next;
    }
    return maxi;
}
