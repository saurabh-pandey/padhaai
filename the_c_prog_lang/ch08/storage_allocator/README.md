This folder contains all the attempts to create a storage allocator in C.
While trying to understand the storage allocator in the book there was a mention of alignment. This
triggered a cascade of exploration starting with understanding alignment, size and offset of
variables.
Next came object pools
Simplicity that the object pool offers is that it holds the same object. Thus is a smaller step
towards the more generic memory pool and storage allocator.
