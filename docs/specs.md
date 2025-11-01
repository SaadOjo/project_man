Project Requirements

- Command line program
- Project Management Software

ARCHITECTURE LOGIC

  PSEUDO CLASSES
  Pseudo classes in our code architecture are .c and coresponding .h files that using naming conventions and 
  structure "object" pointer passing, act somewhat like classes. Since the language natively does not support
  classes, a very strict naming and functional convention need to be followed.

  Object prototypes:

  - Structures
    CLASS_NAME_struture_name_s

  - Functions
    CLASS_NAME_function_name

  Structure allocation, resource and object initialization and collection:
    
    - Make function
        Purpose: 
        Initialize structure to default values without memory allocation

        Prototype: 
        CLASS_NAME_s CLASS_NAME_make();
         
    - Alloc Function
        Purpose:
        Used for cases where resources are internally allocated. Either this or init should be used.

        Prototype: 
        void CLASS_NAME_make(CLASS_NAME_s* s, ... optional required parameters);

    - Init Function
        Purpose: 
        Used for cases where allocated resources are passed. Either this or init should be used.

        Prototype: 
        void CLASS_NAME_make(CLASS_NAME_s* s, ... optional required parameters);
