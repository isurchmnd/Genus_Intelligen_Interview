# Genus_Intelligen_Interview
Repo for codebase used for developing solution to interview homework for Genus Intelligen

Solution for following homework assignment:
Develop the following data structure as homework following the interview. You may use any resources at your disposal, such as books, the web, or brainstorming with a friend, but please do not have someone else write this for you. Deveop a data structure that efficiently stores integer ranges. The code should be readable and maintainable. Simplicity in code is more highly valued than clevernes in the code.

This data structure should:
  - use memory proportional to the number of contiguous ranges, e.g., 1-5, and 25-1000 are two ranges
  - support adding or removing ranges or individual integers in time proportional to the number of ranges
  - suport the querying for the presence of ranges or individual integers in time that is proportional to the base2 logarithm of the number of ranges in the data structure.
  
You may use the data structures in the standard template library but ther is no requirement to do so. If you have questions about this assignment feel free to contact me so that I may clarify requirements and so forth.   


Notes:
Solution uses a vector as the storage, to store Node structures that contain the min and max integer values of each range. 
Additional support for merging ranges if two ranges should overlap, or if adding an integer bridges two ranges so they can become one. 
Written in C++ using visual studio


Known Issue(s):
With multiple iterations through binary search the input data is becoming corrupt and causing the search to hang. This is the root cause of failures with range addition and search functionality. 
