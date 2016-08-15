## C++ concepts and Haskell type classes

Pavel Filonov (pavel.filonov@kaspersky.com)



## Motivation

1. GCC 6.1 Released with C++ concepts support (-fconcepts) <!-- .element: class="fragment" -->
2. A lot of questions about difference between this tow instruments <!-- .element: class="fragment" -->
 * How are C++ concepts different to Haskell type classes? (SO) <!-- .element: class="fragment" -->
 * Understanding C++ Concepts through Haskell Type Classes <!-- .element: class="fragment" -->
 * A Comparison of C++ Concepts and Haskell Type Classes <!-- .element: class="fragment" -->
 * Concepts for C++1y: The Challenge <!-- .element: class="fragment" -->
3. Docendo discimus (by teaching, we learn) <!-- .element: class="fragment" -->



## The problem with C++ templates

The programmer has a set of problems and he decide to use C++

```cpp  
class Problem {
public:
    // ...
};

int main() {
    set<Problem> to_do;

    to_do.insert(Problem{});

    return 0;
}
``` 
<!-- .element: class="fragment" -->



## this is ~~spart~~a problem!

<pre  style="font-size: 10pt; white-space: pre-wrap; word-wrap: break-word; ">
In file included from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:65:0</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/set:60</span>,
                 from <span style="font-weight: bold">SetOfProblems.cpp:1</span>:
/usr/include/c++/6/bits/stl_function.h: In instantiation of ‘<span style="font-weight: bold">constexpr bool std::less&lt;_Tp&gt;::operator()(const _Tp&amp;, const _Tp&amp;) const [with _Tp = Problem]</span>’:
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:1806:11:</span>   required from ‘<span style="font-weight: bold">std::pair&lt;std::_Rb_tree_node_base*, std::_Rb_tree_node_base*&gt; std::_Rb_tree&lt;_Key, _Val, _KeyOfValue, _Compare, _Alloc&gt;::_M_get_insert_unique_pos(const key_type&amp;) [with _Key = Problem; _Val = Problem; _KeyOfValue = std::_Identity&lt;Problem&gt;; _Compare = std::less&lt;Problem&gt;; _Alloc = std::allocator&lt;Problem&gt;; std::_Rb_tree&lt;_Key, _Val, _KeyOfValue, _Compare, _Alloc&gt;::key_type = Problem]</span>’
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:1859:28:</span>   required from ‘<span style="font-weight: bold">std::pair&lt;std::_Rb_tree_iterator&lt;_Val&gt;, bool&gt; std::_Rb_tree&lt;_Key, _Val, _KeyOfValue, _Compare, _Alloc&gt;::_M_insert_unique(_Arg&amp;&amp;) [with _Arg = Problem; _Key = Problem; _Val = Problem; _KeyOfValue = std::_Identity&lt;Problem&gt;; _Compare = std::less&lt;Problem&gt;; _Alloc = std::allocator&lt;Problem&gt;]</span>’
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_set.h:492:40:</span>   required from ‘<span style="font-weight: bold">std::pair&lt;typename std::_Rb_tree&lt;_Key, _Key, std::_Identity&lt;_Key&gt;, _Compare, typename __gnu_cxx::__alloc_traits&lt;_Alloc&gt;::rebind&lt;_Key&gt;::other&gt;::const_iterator, bool&gt; std::set&lt;_Key, _Compare, _Alloc&gt;::insert(std::set&lt;_Key, _Compare, _Alloc&gt;::value_type&amp;&amp;) [with _Key = Problem; _Compare = std::less&lt;Problem&gt;; _Alloc = std::allocator&lt;Problem&gt;; typename std::_Rb_tree&lt;_Key, _Key, std::_Identity&lt;_Key&gt;, _Compare, typename __gnu_cxx::__alloc_traits&lt;_Alloc&gt;::rebind&lt;_Key&gt;::other&gt;::const_iterator = std::_Rb_tree_const_iterator&lt;Problem&gt;; std::set&lt;_Key, _Compare, _Alloc&gt;::value_type = Problem]</span>’
<span style="font-weight: bold">SetOfProblems.cpp:15:27:</span>   required from here
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_function.h:387:20:</span> <span style="font-weight: bold; color: #aa0000">error: </span>no match for ‘<span style="font-weight: bold">operator&lt;</span>’ (operand types are ‘<span style="font-weight: bold">const Problem</span>’ and ‘<span style="font-weight: bold">const Problem</span>’)
       { return <span style="font-weight: bold; color: #aa0000">__x &lt; __y</span>; }
                <span style="font-weight: bold; color: #aa0000">~~~~^~~~~</span>
In file included from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_algobase.h:64:0</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:63</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/set:60</span>,
                 from <span style="font-weight: bold">SetOfProblems.cpp:1</span>:
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_pair.h:369:5:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>candidate: template&lt;class _T1, class _T2&gt; constexpr bool std::operator&lt;(const std::pair&lt;_T1, _T2&gt;&amp;, const std::pair&lt;_T1, _T2&gt;&amp;)
     <span style="font-weight: bold; color: #00aaaa">operator</span>&lt;(const pair&lt;_T1, _T2&gt;&amp; __x, const pair&lt;_T1, _T2&gt;&amp; __y)
     <span style="font-weight: bold; color: #00aaaa">^~~~~~~~</span>
</pre>



                        <pre style="font-size: large; white-space: pre-wrap; word-wrap: break-word; ">
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_pair.h:369:5:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>  template argument deduction/substitution failed:
In file included from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:65:0</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/set:60</span>,
                 from <span style="font-weight: bold">SetOfProblems.cpp:1</span>:
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_function.h:387:20:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>  ‘<span style="font-weight: bold">const Problem</span>’ is not derived from ‘<span style="font-weight: bold">const std::pair&lt;_T1, _T2&gt;</span>’
       { return <span style="font-weight: bold; color: #00aaaa">__x &lt; __y</span>; }
                <span style="font-weight: bold; color: #00aaaa">~~~~^~~~~</span>
In file included from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_algobase.h:67:0</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:63</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/set:60</span>,
                 from <span style="font-weight: bold">SetOfProblems.cpp:1</span>:
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_iterator.h:298:5:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>candidate: template&lt;class _Iterator&gt; bool std::operator&lt;(const std::reverse_iterator&lt;_Iterator&gt;&amp;, const std::reverse_iterator&lt;_Iterator&gt;&amp;)
     <span style="font-weight: bold; color: #00aaaa">operator</span>&lt;(const reverse_iterator&lt;_Iterator&gt;&amp; __x,
     <span style="font-weight: bold; color: #00aaaa">^~~~~~~~</span>
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_iterator.h:298:5:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>  template argument deduction/substitution failed:
In file included from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:65:0</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/set:60</span>,
                 from <span style="font-weight: bold">SetOfProblems.cpp:1</span>:
<span style="font-weight: bold">/usr/include/c++/6/bits/stl_function.h:387:20:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>  ‘<span style="font-weight: bold">const Problem</span>’ is not derived from ‘<span style="font-weight: bold">const std::reverse_iterator&lt;_Iterator&gt;</span>’
       { return <span style="font-weight: bold; color: #00aaaa">__x &lt; __y</span>; }
                <span style="font-weight: bold; color: #00aaaa">~~~~^~~~~</span>
In file included from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_algobase.h:67:0</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/bits/stl_tree.h:63</span>,
                 from <span style="font-weight: bold">/usr/include/c++/6/set:60</span>,
                 from <span style="font-weight: bold">SetOfProblems.cpp:1</span>:
</pre>



## SOS!

<pre  style="font-size: large; white-space: pre-wrap; word-wrap: break-word; ">
<span style="font-weight: bold">ConceptOfProblems.cpp:</span> In function ‘<span style="font-weight: bold">int main()</span>’:
<span style="font-weight: bold">ConceptOfProblems.cpp:28:16:</span> <span style="font-weight: bold; color: #aa0000">error: </span>template constraint failure
     set&lt;Problem<span style="font-weight: bold; color: #aa0000">&gt;</span> to_do;
                <span style="font-weight: bold; color: #aa0000">^</span>
<span style="font-weight: bold">ConceptOfProblems.cpp:28:16:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>  constraints not satisfied
<span style="font-weight: bold">ConceptOfProblems.cpp:28:16:</span> <span style="font-weight: bold; color: #00aaaa">note: </span>  concept ‘<span style="font-weight: bold">LessComparable&lt;Problem&gt;()</span>’ was not satisfied
</pre>

```cpp
template<typename T>
concept bool LessComparable()
{
  return requires (T a, T b)
  {
    { a < b } -> bool;
  };
}
```
<!-- .element: class="fragment" data-fragment-index="1" -->

Hmm... I guess I saw his before in Haskell
<!-- .element: class="fragment" data-fragment-index="2" -->

```haskell
class LessComparable a where
    (<) :: a -> a -> Bool
```
<!-- .element: class="fragment" data-fragment-index="2" -->



### Polymorphism

|             |   Static   |      Dynamic    |
|:-----------:|:----------:|:---------------:|
|  **C++**    |templates   |virtual functions|
| **Haskell** | forall     | type classes    |



### Find the difference
C++ style
```cpp
// Concept
template<class T> concept bool Stringable = 
    requires(const T& a) {
        {to_string(a)} -> string;
    };
// Modelling
class Person {
    //...
    friend string to_string(const Person&);
};
// Algorithm
string bold(const Stringable& s) {
    return "<b>" + to_string(s) + "</b>";
}
// Instantiation
cout << bold(Person{"John", "Smith"}) << endl;
```



### Templates instantiation
Code after concepts check

```cpp
// Modelling
class Person {
    //...
    friend string to_string(const Person&);
};
// Algorithm
string bold(const Person& s) {
    return "<b>" + to_string(s) + "</b>";
}
// Instantiation
cout << bold(Person{"John", "Smith"}) << endl;
```



### Try and see
https://gcc.godbolt.org/

g++-6.1 -S -fconcepts -O0 -fverbose-asm stringable.cpp | c++filt

```
std::__cxx11::basic_string<...> bold<Person>(Person const&):
        push    rbp     
        mov     rbp, rsp  
        push    rbx     
        sub     rsp, 88   
        ; ...
        call    to_string[abi:cxx11](Person const&)     
        ; ...
        mov     rax, QWORD PTR [rbp-88]   #, <retval>
        add     rsp, 88   
        pop     rbx       
        pop     rbp       
        ret
```



Haskell style
```haskell
-- Type class
class Stringable a where
    toString :: a -> String

data Person = Person {firstname :: String, lastname :: String}

-- Instance
instance Stringable Person where
    toString p = take 1 (firstname p) ++ ". " ++ lastname p
 
-- Algorithm
bold :: Stringable a => a -> String
bold a = "<b>" ++ toString a ++ "</b>"

--Instantiation
putStrLn $ bold $ Person "John" "Smith"
```



### Dictionary passing
```haskell
data Stringable a = Stringable { toString :: a -> String }

data Person = Person { firstname :: String, lastname :: String }

personToString :: Person -> String
personToString p = take 1 (firstname p) ++ ". " ++ lastname p

dStringablePerson :: Stringable Person
dStringablePerson = Stringable { toString = personToString }

bold :: Stringable a -> a -> String -- '=>' became '->'
bold dStringlable a = "<b>" ++ toString dStringlable a ++ "</b>"

-- the context is now a parameter!
putStrLn $ bold dStringablePerson $ Person "John" "Smith"
```
Type classes are a way to pass instance dictionaries implicitly
<!-- .element: class="fragment"-->



### We need to go deeper
```
ghc -ddump-inlinings -ddump-simpl -dsuppress-module-prefixes \
    -dsuppress-idinfo -dsuppress-coercions \
    -dsuppress-type-applications -fforce-recomp -O0 main.hs
```
```haskell
toString :: forall a_alG. Stringable a_alG => a_alG -> String
toString = \ (@ a_alG) (tpl_B1 :: Stringable a_alG) ->
    case tpl_B1 of tpl_B1 { D:Stringable tpl_B2 tpl_B3 -> tpl_B2 }

bold :: forall a. Stringable a => a -> String
bold = \ (@ a) ($dStringable :: Stringable a) (a1 :: a) ->
    ++
      (unpackCString# "<b>"#)
      (++ (toString $dStringable a1) (unpackCString# "</b>"#))
$fStringablePerson :: Stringable Person
$fStringablePerson = D:Stringable $ctoString $cfromString

putStrLn
    (bold
       $fStringablePerson
       (Person (unpackCString# "John"#) (unpackCString# "Smith"#)))
```
<!-- .element: class="fragment"-->



### Comparison

* Haskell type classes: <!-- .element: class="fragment" data-fragment-index="1"-->
    * Generic <!-- .element: class="fragment" data-fragment-index="1"-->
    * Compile-time checks <!-- .element: class="fragment" data-fragment-index="1"-->
    * Runtime polymorphism <!-- .element: class="fragment" data-fragment-index="1"-->
* C++ concepts: <!-- .element: class="fragment" data-fragment-index="2" -->
    * Generic <!-- .element: class="fragment" data-fragment-index="2"-->
    * Compile-time checks <!-- .element: class="fragment" data-fragment-index="2"-->
    * Function overloading (compile-time polymorphism) <!-- .element: class="fragment" data-fragment-index="2"-->

What is the analogue in C++ for type classes? <!-- .element: class="fragment"-->



### C++ parametrized abstract class
```cpp
template<typename T> struct Stringable {
    virtual string to_string(const T&) const = 0;
};
```
<!-- .element: class="fragment"-->
```cpp
template<typename T> struct StringablePerson;
template<> struct StringablePerson<Person>: Stringable<Person> {
    string to_string(const Person& p) const override {
        return p.firstname().substr(0, 1) + ". " + p.lastname();
    }
};

StringablePerson<Person> dStringable;

template<typename T>
string bold(const Stringable<T>& dict, const T& a) {
    return "<b>" + dict.to_string(a) + "</b>";
}

cout << bold(dStringable, Person{"John", "Smith"}) << endl;
```
<!-- .element: class="fragment"-->



### Conclusions

* C++ concepts and Haskell type classes just look the same
<!-- .element: class="fragment"-->
* But:
<!-- .element: class="fragment"-->
    * they have different scope
    <!-- .element: class="fragment"-->
    * and different purpose
    <!-- .element: class="fragment"-->
* Nearest analog to type classes in C++ is parametrized abstract classes
<!-- .element: class="fragment"-->



### References
1. ISO/IEC JTC1 SC22 WG21 N
4377 IT -- Programming Languages — C++ Extensions for Concepts - [Paper](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4377.pdf)
2. Александр Фокин, От Concepts к Concepts Lite - [Video](https://www.youtube.com/watch?v=482JCDghZ8s)
3.  Andrew Sutton, Defining Concepts - [Blogpost](https://accu.org/index.php/journals/2198)
4. Tom Honermann, Why Concepts didn't make c++17 - [Blogpost](http://honermann.net/blog/2016/03/06/why-concepts-didnt-make-cxx17/)
5.  Andrew Sutton, Origin - [Source](https://github.com/asutton/origin)
6. How are C++ concepts different to Haskell typeclasses? - [SO](http://stackoverflow.com/questions/32124627/how-are-c-concepts-different-to-haskell-typeclasses)
7. Miran Lipovača, Learn You a Haskell for Great Good! - [eBook](http://learnyouahaskell.com/)



### More references
9. OOP vs Type classes - [Blogpost](https://wiki.haskell.org/OOP_vs_type_classes)
10. Implementing, and Understanding Type Classes - [Blogpost](http://okmij.org/ftp/Computation/typeclass.html)
11. Parametric Polymorphism in Haskell, Ben Deane - [Slides](http://sm-haskell-users-group.github.io/pdfs/Ben%20Deane%20-%20Parametric%20Polymorphism.pdf)
12. Understanding C++ Concepts through Haskell Type Classes, Bartosz Milewski - [Video](https://vimeo.com/17031425)
13. A comparison of C++ concepts and Haskell type classes, Jean-Philippe Bernardy and others - [Paper](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.566.8506&rep=rep1&type=pdf)
14. Concepts for C++1y: The Challenge, B. Stroustrup - [Slides](http://www.cs.ox.ac.uk/ralf.hinze/WG2.8/28/slides/bjarne.pdf)
16. Instances and Dictionaries, Jonathan Fischoff - [Blogpost](https://www.schoolofhaskell.com/user/jfischoff/instances-and-dictionaries)



## Thank you for your attention!

Contacts:
<table>
<tbody>
<tr><td>email</td><td>Pavel.Filonov@kaspersky.com</td></tr>
<tr><td>github</td><td><a href="https://github.com/sdukshis">sdukshis</a></td></tr>
<tr><td>skype</td><td>filonovpv</td></tr>
<tr><td>twitter</td><td>@filonovpv</td></tr>
</tbody>
</table>
