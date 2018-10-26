import com.mongodb.client.*;
import org.bson.Document;

public class Main {
    public static void main(String[] args)  {

        MongoClient mongoClient = MongoClients.create();
        MongoDatabase database = mongoClient.getDatabase("students");
        MongoCollection<Document> collection = database.getCollection("grades");

        MongoCursor<Document> cursor =
                collection.find(new Document("type", "homework"))
                          .sort(new Document("student_id", 1).append("score", 1))
                          .iterator();
        try {
            int studentId = -1;
            while (cursor.hasNext()) {
                Document doc = cursor.next();
                int curStudentId = doc.getInteger("student_id");
                if (curStudentId != studentId) {
                    collection.deleteOne(doc);
                }
                studentId = curStudentId;
                System.out.println(doc.toJson());
            }
        } finally {
            cursor.close();
        }
    }
}
