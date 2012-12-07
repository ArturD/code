#!/usr/bin/env python

def all_combos(choices):
    """
    Given a list of items (a,b,c,...), generates all possible combinations of
    items where one item is taken from a, one from b, one from c, and so on.

    For example, all_combos([[1, 2], ["a", "b", "c"]]) yields:

        [1, "a"]
        [1, "b"]
        [1, "c"]
        [2, "a"]
        [2, "b"]
        [2, "c"]
    """
    if not choices:
        yield []
        return

    for left_choice in choices[0]:
        for right_choices in all_combos(choices[1:]):
            yield [left_choice] + right_choices
import copy
class Node:
    def __init__(self, value, children=[]):
        self.value    = value
        self.children = copy.deepcopy(children)

    def all_subtrees(self, max_depth):
        yield Node(self.value)

        if max_depth > 0:
            # For each child, get all of its possible sub-trees.
            child_subtrees = [list(self.children[i].all_subtrees(max_depth - 1)) for i in range(len(self.children))]

            # Now for the n children iterate through the 2^n possibilities where
            # each child's subtree is independently present or not present. The
            # i-th child is present if the i-th bit in "bits" is a 1.
            for bits in xrange(1, 2 ** len(self.children)):
                for combos in all_combos([child_subtrees[i] for i in range(len(self.children)) if bits & (1 << i) != 0]):
                    yield Node(self.value, combos)
    
    @property
    def flat(self):
        d = [self.value]
        for x in self.children:
            d += x.flat
        return d
    @property
    def size(self):
        d = 1
        for x in self.children:
            d += x.size
        return d

    def normalize(self):
        flat = self.flat
        flat.sort()
        m = {}
        for i in xrange(0,len(flat)):
            m[flat[i]] = i+1
        self.apply(m)

    def apply(self,m):
        self.value = m[self.value]
        for x in self.children:
            x.apply(m)
        
    def __str__(self):
        """
        Display the node's value, and then its children in brackets if it has any.
        """
        st = ""
        for x in self.children:
            st += "%s %s " %(self.value, x.value)
        for x in self.children:
            st += str(x)
        return st

    def __repr__(self):
        return str(self)

tree = Node(1,
[
    Node(2),
    Node(3,
    [
        Node(4,[Node(5,[Node(6,[Node(7)])])]),
        Node(8,[Node(9),Node(10),Node(11),Node(12),Node(13,[Node(14)])]),
        Node(15)
    ])
])

from random import *
for subtree in tree.all_subtrees(4):
    if subtree.size > 2:
        subtree.normalize()
        name = "in/mul.%04.d.%d.in" % (subtree.size,randint(10**3,10**20))
        with open(name, "w") as f:
          f.write("%s\n%s" % (subtree.size, subtree))
