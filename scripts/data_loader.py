import pymongo
from pymongo import MongoClient

client = MongoClient("mongodb://localhost:27017/")
db = client["trie_db"]
collection = db["words"]


collection.delete_many({})

#testing for insertion
words = [
    "search", "season", "seal", "see", "seem", "seen", "select",
    "self", "sell", "semantic", "seminar", "senior", "sense"
]


collection.insert_many([{"word": w} for w in words])

#logging
print(f"[INFO] Inserted {len(words)} words into MongoDB.")
