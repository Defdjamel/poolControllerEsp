
const {onRequest} = require("firebase-functions/v2/https");
const logger = require("firebase-functions/logger");
const functions = require("firebase-functions/v1");
const {initializeApp} = require("firebase-admin/app");
const admin = require("firebase-admin");
const {getFirestore, FieldValue} = require("firebase-admin/firestore");

// const serviceAccount = require("../poolcontroller_key_local.json");
initializeApp({
//   credential: admin.credential.cert(serviceAccount),
});

const db = getFirestore();

// Create and deploy your first functions
// https://firebase.google.com/docs/functions/get-started

exports.updatePh = onRequest(async (request, response) => {
  logger.info("Hello logs! updatePh", {structuredData: true});
  const deviceId = request.body.mac;
  const phVal = parseFloat(request.body.ph);
  const devicesREf = db.collection("prod/data/devices/" + deviceId + "/ph");

  // // Add a new document with a generated id.
  const res = await devicesREf.add({
    value: phVal,
    created_at: FieldValue.serverTimestamp(),
  });

  console.log("Added document with ID: ", res.id);
  response.send({status: "OK"});
});

exports.helloWorldGet = onRequest((request, response) => {
  logger.info("Hello logs!", {structuredData: true});
  response.send({status: "OK"});
});

exports.sayHello = onRequest(
    (req, res) => {
        
      res.status(200).send(req.body.mac);
    },
);
// test V1
exports.date = functions.https.onRequest((req, res) => {
  res.status(200).send("Hello get!");
});
