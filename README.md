Insertion Function - insert NAME ID O(log n)
My insert function is made up of a helper function as well as checks to ensure that the input is a valid
name with quotation marks and that the ufid has 8 digits. These checks are O(1) as they are simple
checks at a certain position in the string and thus don’t contribute to the overall time complexity. If all
the parameters match, the insert moves on to the insert helper function, which recursively determines
where the node should be by comparing with nodes in its path thus far. Inserting at the leaf is O(1) but
retracing to the root is O (log n) as even though the tree is already balanced, the tree must reach the
bottom to insert a new node. Within my insertion function, if the tree becomes unbalanced, we must
rotate the nodes. The rotation of nodes is O(1) as well as finding the balance factor is O(1) as there is no
traversal or recursion involved, and simply only calling commands on the node. Overall, the insertion
function has a time complexity of O (log n).
Remove Function - remove ID O(log n)
In my remove function, I first search through the entire tree to ensure that the node is a valid node and
has a position in the tree. Because my search function is O(log n), that is included within the time
complexity of the remove function. After verifying that the node exists, the remove helper has very
similar logic as the insertion function, as it traverses the tree recursively and locates the location where
the node to be deleted is. The remove function traverses down one path to ensure efficiency and
accomplishes this in O (log n) time to eliminate many other paths. Once the path is found, the node is
checked if it has children which is a O(1) command. The node is deleted and the children take its place. If
the node has two children, the node is deleted but the in-order Successor is identified through the
inOrderSuccessor function that traverses the right of the node and down to the left most node of the
right subtree. This is about a O(1) to O(log n) complexity, depending on the location of the node. Due to
the recuring nature of traversing to the node being deleted, the searching function, and the
inOrderSuccessor function, we are left with O(3logn) or an overall O(log n) worst time complexity upon
dropping the constants.
Search Function - search ID O(log n)
My search ID function consists of traveling through all nodes recursively to identify the node where the
id resides. The searching functions takes advantage of the binary nature of the AVL tree and splits the
task into finding out if the id being searched is greater than or less than the node currently being
traversed and takes the path where the id would be. This logic allows the function to establish an O(log n)
time complexity.
Gator AVL Project
Search Name Function - search NAME O(n)
The searchname function completes a Breadth First Search to traverse through the AVL tree and identify
the node where name resides. Because there is not the ease of utilizing the binary nature of the AVL tree,
we must traverse through all the nodes to find the node where the names are equal, at the chance that
there are multiple names contained within the entire AVL tree. Because this searching algorithm passes
through all nodes within the tree, the time complexity is O(n).
printInOrder Function – O(n)
The printInOrder function utilizes two helper functions: clear() and InOrder(). The clear function clears all
of the saved nodes within the vectors that store the nodes in in order, post order, and pre order which
has a time complexity of O(n). The InOrder() function establishes recursion to travel through all the
nodes within the tree, starting with the left most node then the root and the closest right node,
traversing through all the nodes in the end. The node names and values are then saved within the in
order vector, ultimately resulting in a time complexity of O(n).
printPostorder Function – O(n)
The printPostOrder function utilizes two helper functions: clear() and postOrder(). The clear function
clears all of the saved nodes within the vectors that store the nodes in in order, post order, and pre order
which has a time complexity of O(n). The postOrder() function establishes recursion to travel through all
the nodes within the tree, starting with the left most node then the closest right node, and then the root
node, traversing through all the nodes in the end. The node names and values are then saved within the
post order vector, ultimately resulting in a time complexity of O(n).
printPreorder Function – O(n)
The printPreOrder function utilizes two helper functions: clear() and PreOrder(). The clear function clears
all of the saved nodes within the vectors that store the nodes in in order, post order, and pre order which
has a time complexity of O(n). The PreOrder() function establishes recursion to travel through all the
nodes within the tree, starting with the root node then the left and the right nodes, traversing through
all the nodes in the end. The node names and values are then saved within the pre order vector,
ultimately resulting in a time complexity of O(n).
printLevelCount Function – O(1)
The print level count function has a time complexity of O(1), as it measures the longest path of nodes
within the tree, which is equal to the height of the root node, thus getting the root node’s height is only
a O(1) instruction.
Gator AVL Project
removeInorder Function - removeInorder N O(n)
The remove in order function utilizes the inOrder() function as a helper function, which already has a
time complexity of O(n). With this function, the function can gain access to the list of all the nodes in
order, where it can remove the specified node at the spot N. This is an O(1) instruction, but because the
inOrder() function is needed to retrieve all the nodes in order, the entire function has a time complexity
of O(n).
