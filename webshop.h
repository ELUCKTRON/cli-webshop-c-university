#ifndef Webshop_h
#define Webshop_h

typedef struct {
  char *name;
  int price;
  int quantity;
} Product;

typedef struct {
  int maxsize;
  Product **products;
  int size;

} Store;

typedef struct {
  int maxsize;
  Product **products;
  int size;
} Cart;

int findPrice(char *name, Store *s);
int subtractFromStore(Product *p, Store *s);
int insertToStore(Product *p, Store *s);
void cleanupStore(Store *s);
int insertToCart(Product *p, Cart *c);
void cleanupCart(Cart *c);
void StoreReader(Store *store);
void CartReader(Cart *Cart);

#endif