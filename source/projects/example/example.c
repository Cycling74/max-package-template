// see https://github.com/Cycling74/max-sdk/blob/main/source/basics/simplemax/simplemax.c
// Jeremy Bernstein

#include "ext.h"         // standard Max include, always required
#include "ext_obex.h"    // required for new style Max object

////////////////////////// object struct
typedef struct _example {
	t_object ob;    // the object itself (must be first)
} t_example;

///////////////////////// function prototypes
//// standard set
void* example_new(t_symbol* s, long argc, t_atom* argv);
void  example_free(t_example* x);
void  example_assist(t_example* x, void* b, long m, long a, char* s);

//////////////////////// global class pointer variable
void* example_class;


void ext_main(void* r) {
	t_class* c;

	c = class_new("example", (method)example_new, (method)example_free, (long)sizeof(t_example), 0L /* leave NULL!! */, A_GIMME, 0);

	/* you CAN'T call this from the patcher */
	class_addmethod(c, (method)example_assist, "assist", A_CANT, 0);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	example_class = c;

	post("I am the example object");
}

void example_assist(t_example* x, void* b, long m, long a, char* s) {
	if (m == ASSIST_INLET) {    // inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {    // outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void example_free(t_example* x) {
	;
}


void* example_new(t_symbol* s, long argc, t_atom* argv) {
	t_example* x = NULL;
	long       i;

	if ((x = (t_example*)object_alloc(example_class))) {
		object_post((t_object*)x, "a new %s object was instantiated: %p", s->s_name, x);
		object_post((t_object*)x, "it has %ld arguments", argc);

		for (i = 0; i < argc; i++) {
			if ((argv + i)->a_type == A_LONG) {
				object_post((t_object*)x, "arg %ld: long (%ld)", i, atom_getlong(argv + i));
			}
			else if ((argv + i)->a_type == A_FLOAT) {
				object_post((t_object*)x, "arg %ld: float (%f)", i, atom_getfloat(argv + i));
			}
			else if ((argv + i)->a_type == A_SYM) {
				object_post((t_object*)x, "arg %ld: symbol (%s)", i, atom_getsym(argv + i)->s_name);
			}
			else {
				object_error((t_object*)x, "forbidden argument");
			}
		}
	}
	return (x);
}
