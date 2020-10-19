# median-comparison
## Building
Run `make` in the project root directory.

## Usage
First, generate test data:

```
python3 generate_testfiles.py
```

(The amount of numbers to generate can be modified in that script.)

Then, run the program:

```
./mc
```

Example output is shown below.

## Example Output
```
calculating median on index 499999 of 999999 elems...
quicksort median                                2149523045
array quicksort                                 2149523045
array std sort                                  2149523045
randomized select                               2149523045
vector median of medians only (approximative)   2149866506
vector median of medians + quickselect (exact)  2149523045
wirth kth element                               2149523045
nth element                                     2149523045
--------------------
Results: 
--------------------
array quicksort                                 :   112.1097ms
array std sort                                  :    59.8321ms
init                                            :    67.5942ms
nth element                                     :     5.7105ms
quicksort median                                :    76.1378ms
randomized select                               :     8.8619ms
vector median of medians + quickselect (exact)  :    22.3934ms
vector median of medians only (approximative)   :    11.3237ms
wirth kth element                               :     8.5368ms
--------------------
```