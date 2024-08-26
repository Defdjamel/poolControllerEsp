/**
 * Import function triggers from their respective submodules:
 *
 * const {onCall} = require("firebase-functions/v2/https");
 * const {onDocumentWritten} = require("firebase-functions/v2/firestore");
 *
 * See a full list of supported triggers at https://firebase.google.com/docs/functions
 */

const {onRequest} = require("firebase-functions/v2/https");
const logger = require("firebase-functions/logger");
const functions = require("firebase-functions/v1");
const {initializeApp} = require("firebase-admin/app");
const {getFirestore, FieldValue} = require("firebase-admin/firestore");
initializeApp();

const db = getFirestore();

// Create and deploy your first functions
// https://firebase.google.com/docs/functions/get-started

exports.updatePh = onRequest(async (request, response) => {
  logger.info("Hello logs! helloWorld2", {structuredData: true});
  const deviceId = "MAC_ADRESS";
  const phVal = 12.6;
  const devicesREf = db.collection("prod/data/devices/" + deviceId + "/ph");

  // Add a new document with a generated id.
  const res = await devicesREf.add({
    name: "PH",
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
      res.status(200).send(req.query);
    },
);
// test V1
exports.date = functions.https.onRequest((req, res) => {
  res.status(200).send("Hello get!");
});
