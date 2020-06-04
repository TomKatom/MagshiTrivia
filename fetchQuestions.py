import requests
import pymongo

def printAsciiArt():
    print('''
████████ ██████  ██ ██    ██ ██  █████      
   ██    ██   ██ ██ ██    ██ ██ ██   ██     
   ██    ██████  ██ ██    ██ ██ ███████     
   ██    ██   ██ ██  ██  ██  ██ ██   ██     
   ██    ██   ██ ██   ████   ██ ██   ██                                                                           
    ''')

def fetchQuestions(url):
    r = requests.get(url)
    return r.json()["results"]

def questionNotInDB(collection, question):
    result = collection.count_documents({"question" : question})
    return not result
def handleQuestions(questions, collection):
    for question in questions:
        questionText = question["question"]
        questionText = questionText.replace("&quot;", "'")
        questionText = questionText.replace("&#039;", "'")
        questionObject = { "question" : questionText, "correct_answer": question["correct_answer"], "incorrect_answers" : question["incorrect_answers"] } 
        # print("Question: " + questionText + "\n" + "Correct Answer: " + question["correct_answer"] + "\n" + "Wrong Answers: " + str(question["incorrect_answers"]) + "\n")
        if questionNotInDB(collection, questionText):
            result = collection.insert_one(questionObject)
            print(result)

def main():
    client = pymongo.MongoClient("mongodb://localhost:27017/")
    db = client.Trivia
    printAsciiArt()
    handleQuestions(fetchQuestions("https://opentdb.com/api.php?amount=10&type=multiple"), db.questions)

if __name__ == "__main__":
    main()