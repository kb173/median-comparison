import random

num_iterations = 1000000

with open("testdata", "w") as file:
    # Write the number of lines to expect
    file.write("%s\n" % num_iterations)
    
    # Write lots of random numbers
    for i in range(0, num_iterations):
        # Between 0 and the maximum of uint32
        file.write("%s\n" % random.randint(0, 4294967295))
