## Style Guide 

- camelCase for *regular variables* and *function* names.

- CAPITAL_SNAKE_CASE for *const* and *constexpr variables*.

- TitleCase for *classes* and *structs*.

- kebab-case for *file* and *folder* names.

- Use nouns for *variable*, *class*, and *struct* names.

- Use verbs for the first word of every *function* and *method* name ("is", "does" are verbs btw).

- If the object *method* only serves to return the value of an object *member*, you can use the *member* name even if its a noun.

- Format your *if-else* statements like this:

  ![alt text](sample-photos-for-guide/if-else-format.png)

- **BE DESCRIPTIVE WITH YOUR NAMES**. Do not use single letter names like *i* for *for loops*. At least use the name *index* if you're using the *for loop* to access an array or array-like object, or *counter* for when you just need to loop a certain amount of times.

  ![alt for-loop-iterator-names.png](sample-photos-for-guide/for-loop-iterator-names.png)
  


## Coding Guide

- **NO NON-CONSTANT GLOBAL VARIABLES**. If you need a *global variable* that changes, just declare it at *main()* and add it as a parameter in whatever function you need it for.

  ![const-glbal-variable-sample.png](sample-photos-for-guide/image.png)

- Initialize all variables in your function at the beginning of your function. You can assign them later if they don't need to be assigned anything for now.
  
  ![initialize-variables-at-beginning.png](sample-photos-for-guide/initialize-variables-at-beginning.png)

- Also, when running a data structure that can change size through a loop that uses its size as part of its condition, **DO NOT ADD A BLOCK CODE THAT WILL ALTER ITS SIZE INSIDE THE LOOP**.


  ![iteration-over-dynamic-size-wrong-way.png](sample-photos-for-guide/iteration-over-dynamic-size-wrong-way.png)
  ![iteration-over-dynamic-size-right-way.png](sample-photos-for-guide/iteration-over-dynamic-size-right-way.png)


- If a *struct* could do the job, just use a *struct*. Avoid using *array[]*. I've had a lot of trouble using *array[]* in my last project. I'm kinda traumatized. Just use *std::array* instead if you really need one.

  ![prefer-structs-to-arrays.png](sample-photos-for-guide/image-1.png)

- If you feel your function is taking too many parameters, make a struct to store those parameters in instead.

  ![use-structs-to-store-parameters.png](sample-photos-for-guide/use-structs-to-store-parameters.png) 

- There are two types of *increment* (++) / *decrement* (--) operators which depends on their placement on the variable: *pre-* and *post-*. In *pre-*, the value is first incremented/decremented before being used while in *pro-*, the value is first used before being incremented/decremented.
  ![increment-decrement-code.png](sample-photos-for-guide/increment-decrement-code.png) 
  ![increment-decrement-output.png](sample-photos-for-guide/increment-decrement-output.png) 


  
