typedef struct routeTable{
	int cost;
	int nexthop;
	int dest;
	struct routeTable *next;
}routeTable;

typedef struct router{
	int neighbour[15];
	int n_neighbour;
	routeTable *rt;
	int rAddr;
	int status;
}router;



