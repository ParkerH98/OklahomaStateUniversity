# Filename: pymysort.py
# Author: Parker Hague
# Course: CS3363
# Assignment: Program4
# Due: Oct. 17th, 2020, 11:59 PM
# Submitted: Oct. 17th, 2020

# import time

# list comprehension quicksort algorithm

def pymysort(li):
    if li == []:
        return li #returns empty list if input list is empty
    pivot = li[0] # sets pivot to first element in list
    lower = [ i for i in li[1:] if i <= pivot ] # adds elemets to "lower" that are less than or equal to pivot
    higher = [ i for i in li[1:] if i > pivot ] # adds elemets to "higher" that are less than or equal to pivot
    return pymysort(lower) + [pivot] + pymysort(higher) # returns a sorted list concatenating lower, pivot, and higher



# def quickSort(arr):
#     less = []
#     pivotList = []
#     more = []
#     if len(arr) <= 1:
#         return arr
#     else:
#         pivot = arr[0]
#         for i in arr:
#             if i < pivot: less.append(i)
#             elif i > pivot: more.append(i)
#             else: pivotList.append(i)
#         less = quickSort(less)
#         more = quickSort(more)
#         return less + pivotList + more



# I deleted the test array because it contained
# 200,000 entries which was just excessive to 
# include in my submission.

# the below was used to analize the efficiency of the algorithms

#Logging execution time for recursive sort
# start_time2 = time.time()
# quickSort(array)
# print (time.time() - start_time2, "Seconds to Execute Recursion")
# print()


#Logging execution time for list comprehension sort
# start_time1 = time.time()
# pymysort(array)
# print (time.time() - start_time1, "Seconds to Execute List Comprehension")
# print()

# print (pymysort(array))
#print (quickSort(array))