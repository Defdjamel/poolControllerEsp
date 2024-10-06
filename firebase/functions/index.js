
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

exports.updateOrp = onRequest(async (request, response) => {
  const deviceId = request.body.mac;
  const val = parseFloat(request.body.orp);
  const devicesREf = db.collection("prod/data/devices/" + deviceId + "/orp");
  // // Add a new document with a generated id.
  const res = await devicesREf.add({
    value: val,
    created_at: FieldValue.serverTimestamp(),
  });

  console.log("Added document with ID: ", res.id);
  response.send({status: "OK"});
});

exports.getLastVersion = onRequest(
    async (req, res) => {

   const cityRef = db.collection('prod').doc('version');
  const doc = await cityRef.get();
  if (!doc.exists) {
    console.log('No such document!');
  } else {
    console.log('Document data:', doc.data());
}

        
      res.status(200).send(doc.data());
    },
);
// test V1
exports.date = functions.https.onRequest((req, res) => {
  res.status(200).send("Hello get!");
});
exports.updateVersion = onRequest(async (request, response) => {
  
  const version = request.body.version;
  const devicesRef = db.collection("prod").doc("version"); // Chemin vers le document à mettre à jour
  
  try {
    // Mettre à jour la version dans le document "version"

    const res = await devicesRef.set({
      ESP: version
    }, { merge: true });

    console.log("Document mis à jour avec succès");
    response.send({status: "OK", message: "Version updated successfully."});
  } catch (error) {
    console.error("Erreur lors de la mise à jour :", error);
    response.status(500).send({status: "ERROR", message: "Failed to update version."});
  }

});
