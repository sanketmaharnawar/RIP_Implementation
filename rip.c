#include "rip.h"
//4 1 2 1 2 3 0 1 3 1 2

router rou[15];
int n_router = 0;
void createRouter(int n_router);
void deleteRouter(int A);
void updateAll(int A, int C);
void updateTable(int A, int B);
void toUpdate(int A);
int main() {
	int i, j, t, c, d, nRou;
	printf("Enter number of routers to be added in network : ");
	scanf("%d", &nRou);
	createRouter(nRou);
	//printf("Initial Routing Tables \n\n");
	//printAllTables();
	for(i = 0; i < n_router; i++)
		toUpdate(i);
	
	while (1) {
		printf("\n\n\n    ********* MENU *********\n\t1. Add Routers\n\t2. Delete Router\n\t3. Show Router Table\n\t4. Exit\n\n\tEnter Option : ");
		
		scanf("%d", &c);

		switch(c){
			case 1 :
				printf("Enter number of routers to be added in network : ");
				scanf("%d", &nRou);
				createRouter(nRou);
				break;
	
			case 2 :
				printf("Enter Router Number to Delete :");
				scanf("%d", &d);
				deleteRouter(d);
				for(i = 0; i < n_router; i++)
					toUpdate(i);
				break;
	
			case 3 :
				if(printAllTables() != 0) {
					printf("ERROR!\n");
				}
				break;
	
			case 4 :
				exit(0);
				break;
	
			default :
				printf("Invalid Option");
				break;
		}
	}

	for(i = n_router; i < 15; i++)
		rou[i].status = -1;
	if(printAllTables() != 0) {
		printf("ERROR!\n");
	}

/*	if(printAllTables() != 0) {
		printf("ERROR!\n");
	}*/
	return 0;
}

void toUpdate(int A) {
	updateAll(A, -1);
	int i;
	for(i = 0; i < rou[A].n_neighbour; i++) {
		updateTable(rou[A].neighbour[i], A);
	}
}

void updateAll(int A, int C) { //C is the calling router. Originally, it is set to -1
	
	if(rou[A].n_neighbour == 1 && C != -1) {
		updateTable(A, C);
		return;
	}
	int i;
	for(i = 0; i < rou[A].n_neighbour; i++) {

		if(rou[A].neighbour[i] != C) {

			updateTable(A, rou[A].neighbour[i]);
			updateAll(rou[A].neighbour[i], A);
		}
	}
	
}

void deleteRouter(int A) {
	rou[A].status = 0;
/*	rou[A].status = 0;
	int i, nr, j, k;
	for(i = 0; i < rou[A].n_neighbour; i++) {
		nr = rou[A].neighbour[i];
		for(j = 0; j < rou[nr].n_neighbour; j++) {
			if(rou[nr].neighbour[j] == A) {
			//Delete from table
				for(k = j; k < rou[nr].n_neighbour; k++) {
					rou[nr].neighbour[k] = rou[nr].neighbour[k+1]; 	
				}
			} 
			rou[nr].n_neighbour--;
		}
		routeTable *tmp;
		tmp = rou[nr].rt;

		while(tmp->nexthop == A) {
			tmp = tmp -> next;
			rou[nr].rt = tmp;
		}
		if(tmp == NULL) {
			continue;
		}
		while(tmp->next != NULL) {
			if(tmp->next->nexthop == A) {
				tmp -> next = tmp->next->next;
			}
		}
		if(tmp->next->nexthop == A) {
			tmp -> next = tmp->next->next;
		}

		
		
	} */
}

void createRouter(int nRou){
	int i = 0, j = 0, t = 0, temp_nei;
	for(i = n_router; i < n_router + nRou; i++) {
		routeTable *temp;
		rou[i].rt = NULL;
		rou[i].rAddr = i;
		rou[i].status = 1;
		printf("Enter no. of neighbours for %d router : ", i);
		scanf("%d", &temp_nei);
		rou[i].n_neighbour = temp_nei;
		printf("Enter the list of neighbours for router %d :", i);
		for(j = 0; j < (rou[i].n_neighbour); j++){
			scanf("%d", &t);
			if(rou[i].rt == NULL) {
				rou[i].rt = (routeTable *) malloc(sizeof(routeTable));
				rou[i].rt->next = NULL;
			}
			else {
				temp = (routeTable *) malloc(sizeof(routeTable));
				temp->next = rou[i].rt ;
				rou[i].rt = temp;
			}
			/*if(t > (rou[i].n_neighbour)){
				j--;
				printf("Invalid");
				continue;
			}*/
			rou[i].rt->cost = 1;
			rou[i].rt->nexthop = t;
			rou[i].rt->dest = t;
			rou[i].neighbour[j] = t;
		}
	}
	n_router += nRou;
}

void updateTable(int A, int B) {
//A sends its routing table to B, B updates it.
	////////////////////////////////////////////////START/////////////////////////////////////////////////////////
	int i, j;
	if(rou[A].status == 0)
		return;
	if(rou[B].status == 0) {
		for(i = 0; i < rou[A].n_neighbour; i++) {
			if(rou[A].neighbour[i] == B) {
				for(j = i; j < rou[A].n_neighbour; j++) {
					rou[A].neighbour[j] = rou[A].neighbour[j+1];
				}
				rou[A].n_neighbour--;
			}
		}
		 
		routeTable *rt1;
		rt1 = rou[A].rt; 
		if(rt1 == NULL)
			return;
		while(rt1->nexthop == B || rt1->dest == B) {
			rt1 = rt1 -> next;
			rou[A].rt = rou[A].rt->next;
			if(rt1 == NULL)
				return;
		}
		if(rt1 == NULL)
			return;
		while(rt1->next != NULL) {
			if(rt1->next->nexthop == B || rt1->dest == B) {
				rt1->next = rt1->next->next;
			}
			rt1 = rt1->next;	
		}
		return;
	}
	
////////////////////////////////////////////////END/////////////////////////////////////////////////////////
	routeTable *tmp1;
	routeTable *tmp2;
	routeTable *tmp3;
	tmp1 = rou[A].rt;
	tmp2 = rou[B].rt;
	int flag = 0;
	while(tmp1 != NULL) {

		tmp2 = rou[B].rt;
		flag = 0;
		tmp3 = tmp2;
		while(tmp2 != NULL) {
	////////////////////////////////////////////////START/////////////////////////////////////////////////////////
			if(rou[tmp2->dest].status == 0) {
				if(tmp3 == tmp2) {
					rou[B].rt = tmp2->next;
				}
				else {
					tmp3->next = tmp2->next;
				}
			}
			tmp3 = tmp2;
	////////////////////////////////////////////////END/////////////////////////////////////////////////////////
			if(tmp1->dest == B) {
				tmp2 = tmp2->next;
				flag = 1;
				continue;
			}
			if(tmp2->dest == tmp1->dest) {
				if(tmp1->cost < tmp2->cost) {
					tmp2->cost = tmp1->cost + 1;
					tmp2->nexthop = A;
				}
				flag = 1;
			}
			tmp2 = tmp2->next;
		}
		if(flag == 0 && rou[tmp1->dest].status != 0) {///////////////////////////////CHANGE
			tmp2 = rou[B].rt;
			while(tmp2->next != NULL) {
				tmp2 = tmp2->next;
			}
			tmp2->next = (routeTable *) malloc(sizeof(routeTable));
			tmp2->next->dest = tmp1->dest;
			tmp2->next->cost = tmp1->cost + 1;
			tmp2->next->nexthop = A;
			tmp2->next->next = NULL;
	
		}
		tmp1 = tmp1 -> next;
	}
}

int printAllTables() {
	int i, j;
	routeTable *tmp = (routeTable *) malloc(sizeof(routeTable));
	if(tmp == NULL) return -1;
	for(i = 0; i < n_router; i++){
		tmp = rou[i].rt;
		if(rou[i].status != 1) continue;
		printf("\n\nTable for Router : %d\n", i);
		printf("---------------------------------\n");
		printf("|  cost\t|  nexthop\t|  dest\t|\n");
		printf("|-------+---------------+-------|\n");
		while(tmp != NULL){
			printf("|  %d\t|  %d\t\t|  %d\t|\n", tmp->cost, tmp->nexthop, tmp->dest);
			tmp = tmp -> next;
		}
		printf("---------------------------------\n\n");
		
		printf("Router Details :\n");
		printf("Router Addr\t\t: 10.1.101.%d\n", rou[i].rAddr);
		printf("Number of Neighbours\t: %d\n", rou[i].n_neighbour);
		printf("Neighbours \t\t: ");
		for(j = 0; j < rou[i].n_neighbour; j++) {
			printf("%d ", rou[i].neighbour[j]);
		}
		printf("\nstatus\t\t\t: %d", rou[i].status);
		printf("\n\n\nxxx\n\n");
		
	}
	return 0;
}
