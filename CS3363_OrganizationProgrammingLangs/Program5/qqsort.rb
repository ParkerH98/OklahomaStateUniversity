
# filename: <qqsort.rb>
# author: <Parker Hague>
# course: <CS3363>, <Fall 2020>
# assignment: <Program 5>
# due: <10/31/2020>, <11:59 PM>
# submitted: <10/31/2020>


def qqsort(arr)
    # returns array if it's empty or contains only one item
    return arr if arr.length <= 1

    # sets a pivot to the first element of the array
    pivot = arr.pop

    # defines two empty arrays to store
    # greater than and less than the pivot
    lessThan, greaterThan = [],  []

    # push to left if i is less than pivot
    # push to right if i is greater than pivot
    # using a ternary operator
    arr.each do |i|
        i < pivot ? lessThan.push(i) : greaterThan.push(i)
    end

    # recursively calls quick sort on left and right arrays
    sortedLeft = qqsort(lessThan)
    sortedRight = qqsort(greaterThan)

    # concatenates left array, pivot, and right array 
    sortedLeft + [pivot] + sortedRight
end

# test case
# toSort = [9, 8, 7, 6, 5, 0, 1, 2, 3, 4]
# p qqsort(toSort)