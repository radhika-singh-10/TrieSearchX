db = db.getSiblingDB('trie_db');
db.createCollection('words');
db.words.insertMany([
  { word: "search" },
  { word: "season" },
  { word: "seal" },
  { word: "see" },
  { word: "semantic" },
  { word: "senior" }
]);
