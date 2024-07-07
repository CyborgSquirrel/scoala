#include "obj.c"

int main() {
  // struct Obj *list = obj_list_new();

  // struct Obj *str = obj_str_new(10, "0123456789");
  // struct ObjList *obj_list = obj_as_list(list);

  // for (int i = 0; i < 20; ++i) {
  //   obj_list_push(obj_list, str);
  // }
  // obj_drop(str);

  // str = obj_list_index(obj_list, 0);
  // obj_print(str);
  // obj_drop(str);
  
  // obj_drop(list);

  struct Obj *dict = obj_dict_new();
  struct Obj *str = obj_str_from_cstring("0123456789");
  struct Obj *str2 = obj_str_from_cstring("abcd");
  struct Obj *str3 = obj_str_from_cstring("bla");

  struct ObjDict *obj_dict = obj_as_dict(dict);
  obj_dict_assign(obj_dict, str, str2);
  obj_dict_assign(obj_dict, str, str3);
  struct Obj *val = obj_dict_index(obj_dict, str);
  if (val != NULL) {
    printf("val = \n");
    obj_print(val);
    obj_drop(val);
  } else {
    printf("wtf\n");
  }

  obj_drop(str);
  obj_drop(str2);
  obj_drop(str3);
  obj_drop(dict);
  
  return 0;
}
