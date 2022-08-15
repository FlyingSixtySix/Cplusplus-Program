from pymongo import MongoClient
from bson.objectid import ObjectId
import json
from bson.json_util import dumps

class AnimalShelter:
    """ CRUD Operations for Animal collection in MongoDB """

    def __init__(self, username, password):
        # Initializing the MongoClient. This helps to
        # access the MongoDB databases and collections.
        self.client = MongoClient('mongodb://%s:%s@localhost:46378' % (username, password))
        self.database = self.client['AAC']

    def create(self, data):
        if data is not None:
            res = self.database.animals.insert_one(data)
            return res.acknowledged
        else:
            raise Exception('Nothing to save, but data parameter is empty')

    def read(self, query):
        if query is not None:
            cur = self.database.animals.find(query)
            return json.loads(dumps(cur))
            #ret = []
            #for doc in cur:
            #    ret.append(doc)
            #return ret
        else:
            raise Exception('Empty query parameter')

    def update(self, query, data):
        if query is not None:
            if data is not None:
                return self.database.animals.update_many(query, data)
            else:
                raise Exception('Empty data parameter')
        else:
            raise Exception('Empty query parameter')

    def delete(self, query):
        if query is not None:
            return self.database.animals.delete_many(query)
        else:
            raise Exception('Empty query parameter')

