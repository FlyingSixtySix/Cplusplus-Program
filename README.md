# Client/Server Development

## How I write maintainable, readable, and adaptable programs

The most important aspect showcased this course was the usage of code modulization.  Storing code related to interfacing with the `animal_shelter` collection in `animal_shelter.py` allowed for re-use in different instances.  For example, when working on project one, I was able to keep the project-specific code in `ProjectOne.ipynb` and `ProjectTwo.ipynb` as opposed to a singular monolithic file.  Developing with modern object-oriented programming techniques certainly helps, such as with classes and class functions.

In the end, while the course was meant to demonstrate how I can make use of a driver class with PyMongo, I felt like it could have all been done in a singular file seeing as no further modifications were made to results returned by the database, such as caching or transforming it into a different data type.

## How I approach problems as a computer scientist

It's simple.  Write re-usable code with purpose.  Avoid unnecessary hoops and document so that future contributors may further development.  My approach did not differ this course and other courses, seeing as how the way I approach problems has not faltered.

## What computer scientists do

The way I see it, computer scientists solve problems, answer questions, and perform various tasks to accomplish goals using modern solutions involving computers.  The work I performed was modularizing database-accessing code, which could help at the start of a large codebase, in case I wanted to add some other layer to the CRUD functions.

