struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
};

struct intrusive_list {
  struct intrusive_node* head;
};

void init_list(struct intrusive_list *l);
struct intrusive_node add_node(struct intrusive_list *l, struct intrusive_node *n);
int remove_node(struct intrusive_list *l, struct intrusive_node *n);

int get_length(struct intrusive_list *l);