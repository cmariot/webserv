# Ft_containers
Le but de ce projet est d'implémenter quelques containers C++ de la bibliothèque standard (Standard Template Library).

## Table of contents
* [Vector](#Vector) 
* [Stack](#Stack)
* [Map](#Map)
* [Iterators](#Iterators) 
* [Utils to implement](#Utils)

### Vector
>  ```= Dynamic contiguous array (SEQUENTIEL)```  
>  * Conteneur séquentiel qui encapsule les tableaux de taille dynamique.  
> *  Les éléments sont stockés de façon contigüe, ce qui signifie que les éléments sont ```accessibles non seulement
via les itérateurs```, mais aussi ```à partir des pointeurs``` classiques sur un élément.  

<details>
    <summary>Propreties STD</summary>  
    
   * Sequence  
      Elements in sequence containers arenordered in a strict linear sequence. Individual elements are accessed by their position in this sequence.   
    
   * Dynamic array    
      Allows direct access to any element in the sequence, even through pointer arithmetics, and provides relatively fast addition/removal of elements at the end of the sequence.  
   * Allocator-aware  
    The container uses an allocator object to dynamically handle its storage needs.  
    
    
<img width="245" alt="Screenshot 2022-08-24 at 12 47 59" src="https://user-images.githubusercontent.com/85625233/186400146-a6ad44ca-437c-41b1-b85d-473b9dd52b49.png">
</details>

### Stack
>  ```= a type of container adaptors with LIFO(Last In First Out ```  
> * uses an encapsulated object of either vector or deque (by default) or list  
> * a new element is ```added at one end``` (top) and an element is ```removed from that end only```

 
### Map
>  ```= Binary Search Tree of key-value pairs, sorted by unique keys.```  
> * Keys are sorted by using the comparison function Compare. Search, removal, and insertion
> * Maps are usually implemented as ```red-black trees```



### Iterators
> Iterators are classified into five categories depending on the functionality they implement  
> ```Random Access Pointers are equivalent to standard pointers.```

<img width="641" alt="Screenshot 2022-08-24 at 13 12 18" src="https://user-images.githubusercontent.com/85625233/186404935-9ab09210-5622-49be-bfe4-0dc20f6d60ca.png">

![image](https://user-images.githubusercontent.com/85625233/194087568-6396c021-7997-4caa-ae50-e728b8f4a96a.png)


### Utils
> * __enable_if__ : <bool B, class T > If B true : public member **typedef T _type_**; otherwise: there is no member typedef.
> * __lexicographical_compare__ :  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)  
> * __equal__  : check if two ranges are equal.
> * __pair__ : Class with 2 elements of type T1 and T2;
> * __make_paire__ : pair<T1,T2> make_pair (T1 x, T2 y);

### To implement  
> The ones to do are vector, map, stack (mandatory) and set (bonus)

<details>
    <summary>The ones to do are vector, map, stack (mandatory) and set (bonus)</summary>   
    
![image](https://user-images.githubusercontent.com/85625233/189640037-e2556d3a-bef5-4f7b-9404-b3643d0f9b72.png)  

</details>


## Sitographie 
* [Bete de site explicatif avec plein d'exemples concrets et concis](https://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/Intro--Conteneurs-Iterateurs.html)  

* [Cours container STL](http://tvaira.free.fr/dev/cours/cours-conteneurs-stl.pdf)
* [Iterators](https://cplusplus.com/reference/iterator/)
* [Red Black Trees](https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/)

#### Somes questions

* [Diff between 'typename' and 'class'](https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates)
* [When is 'typename' necessary](https://stackoverflow.com/questions/7923369/when-is-the-typename-keyword-necessary)
* [Allocator : allocate then construct](https://en.cppreference.com/w/cpp/memory/allocator)

* Vector
    * [Vector Infos](https://docs.microsoft.com/fr-fr/cpp/standard-library/vector-class?view=msvc-170)
    * [**Size** = number of elements / **Capacity** = amount of total space before reallocation](https://stackoverflow.com/questions/6296945/size-vs-capacity-of-a-vector)
    * [**Traits** give information, at the compilation, about certain types thanks to a generic base](https://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/Traits.html)
    * [Why and how using **traits**](https://www.youtube.com/watch?v=bFCzd5U2fsk)
    * [Un itérateur != pointeur  must define 5 required member types by specializing iterator_traits](https://learn.microsoft.com/fr-fr/cpp/standard-library/iterators?view=msvc-170)

* Map 
    * [A Red Black Tree is a Binary Search Tree So let's see how it works?](https://www.programiz.com/dsa/binary-search-tree)
    * [Why C++ uses RedBlackTree](https://github.com/mli42/containers_test.git)
    * [Video explaning RedBlackTree](https://www.youtube.com/watch?v=qvZGUFHWChY)
    * [Red Black Tree = lots of insertions/deletions  AVL Tree = lot of searches](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/) 
    * [Red Black Tree rotations](https://www.youtube.com/watch?v=q4fnJZr8ztY)
    * [How to use rebind ?](https://stackoverflow.com/questions/14148756/what-does-template-rebind-do)
 * Utils
    * [**std::enable_if** is an important function to enable certain types for template specialization](https://leimao.github.io/blog/CPP-Enable-If/)
    * [**std::is_integral** is a Trait class that identifies whether T is an integral type](https://cplusplus.com/reference/type_traits/is_integral/?kw=is_integral)
    * [**std::lexicographical_compare**: true if the range1 < range2 | note: the shorter sequence <  than the longer one](https://leimao.github.io/blog/CPP-Enable-If/)

    * [**std::pair** is a class that couples together a pair of values](https://cplusplus.com/reference/utility/pair/)
    
