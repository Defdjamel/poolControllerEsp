from SCons.Script import DefaultEnvironment
import subprocess
import os

# Obtenir l'environnement de PlatformIO
env = DefaultEnvironment()

# Fonction qui sera appelée après la compilation
def after_build(source, target, env):
    firmware_path = str(target[0])  # Chemin du fichier firmware.bin

    # Définir le chemin de ton script Python d'upload
    script_path = os.path.join(env['PROJECT_DIR'], "upload_firmware.py")

    # Appeler le script Python d'upload avec le chemin du firmware
    result = subprocess.run(["python3", script_path, firmware_path], capture_output=True)

    # Afficher le résultat
    print(result.stdout.decode())
    if result.returncode != 0:
        print("Erreur lors de l'exécution du script d'upload !")
        print(result.stderr.decode())
    else:
        print("Script d'upload exécuté avec succès !")

# Connecter la fonction au processus de compilation de PlatformIO
env.AddPostAction("$BUILD_DIR/firmware.bin", after_build)
