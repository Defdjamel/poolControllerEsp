import boto3
from SCons.Script import DefaultEnvironment
from botocore.exceptions import NoCredentialsError

env = DefaultEnvironment()
def upload_to_s3(file_name, bucket, object_name, profile_name):
    session = boto3.Session(profile_name=profile_name)
    s3_client = session.client('s3')

   

    # Si aucun nom d'objet n'est spécifié, on utilise le nom de fichier
    if object_name is None:
        object_name = file_name

    # Créer une session S3
    s3_client = boto3.client('s3')

    try:
        # Upload du fichier
        s3_client.upload_file(file_name, bucket, object_name)
        print(f"Fichier {file_name} uploadé avec succès dans {bucket}/{object_name}")
        return True
    except FileNotFoundError:
        print("Erreur : Fichier non trouvé.")
        return False
    except NoCredentialsError:
        print("Erreur : Les informations d'identification AWS sont manquantes.")
        return False


# Récupérer les build flags définis dans platformio.ini
build_flags = env.ParseFlags(env['BUILD_FLAGS'])
defines = {k: v for (k, v) in build_flags.get('CPPDEFINES')}
# Afficher les valeurs des build flags
blynk_firmware_version = defines.get('BLYNK_FIRMWARE_VERSION')
print(build_flags)

print(f"BLYNK_FIRMWARE_VERSION: {blynk_firmware_version}")

environment_name = env['PIOENV']
firmware_path = f'.pio/build/{environment_name}/firmware.bin'
file_name = firmware_path # Chemin du fichier à uploader
bucket_name = 'pickme.today'  # Nom du bucket S3
object_name = 'poolcontroller/firmware.bin'  # Optionnel : chemin dans le bucket S3
print("upload_to_s3...")

upload_to_s3(file_name, bucket_name, object_name,"default")