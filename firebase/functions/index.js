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

// Create and deploy your first functions
// https://firebase.google.com/docs/functions/get-started

exports.helloWorld2 = onRequest((request, response) => {
  logger.info("Hello logs! helloWorld2", {structuredData: true});
  response.send({status: "OK"});
});

exports.helloWorldGet = onRequest((request, response) => {
  logger.info("Hello logs!", {structuredData: true});
  response.send({status: "OK"});
});

exports.sayHello = onRequest(
// {cors: [/firebase\.com$/, "flutter.com"]},
    (req, res) => {
      res.status(200).send("Hello get!");
    },
);
