from math import ceil, sqrt
from psd_tools import PSDImage
from PIL import Image, ImageCms

def convert_to_srgb(image):
    """Convert image to sRGB color profile."""
    srgb_profile = ImageCms.createProfile("sRGB")
    
    icc_profile = image.info.get("icc_profile")
    
    if icc_profile:
        try:
            input_profile = ImageCms.ImageCmsProfile(icc_profile)
            return ImageCms.profileToProfile(image, input_profile, srgb_profile)
        except Exception as e:
            print(f"Warnung: ICC-Profil fehlerhaft, keine Konvertierung. Fehler: {e}")
            return image  # Gib das Bild unverändert zurück
    
    return image  # Falls kein ICC-Profil vorhanden, auch unverändert zurückgeben

# def convert_to_srgb(image):
#     """Convert image to sRGB color profile."""
#     srgb_profile = ImageCms.createProfile("sRGB")
#     if "icc_profile" in image.info:
#         input_profile = ImageCms.ImageCmsProfile(image.info["icc_profile"])
#         image = ImageCms.profileToProfile(image, input_profile, srgb_profile)
#     else:
#         image = ImageCms.profileToProfile(image, srgb_profile, srgb_profile)
#     return image

def extract_visible_layers_from_psd(psd_file, sprite_width, sprite_height):
    psd = PSDImage.open(psd_file)
    layers = []
    for layer in psd:
        if layer.is_group() or not layer.visible or layer.name.lower() in ['background', 'hintergrund']:
            continue  # Gruppen, unsichtbare und Hintergrundebenen überspringen
        image = layer.composite()
        image = image.resize((sprite_width, sprite_height))
        image = convert_to_srgb(image)  # Konvertiere zu sRGB
        layers.append(image)
    return layers

def create_spritesheet(layers, output_file, sprite_width, sprite_height):
    num_layers = len(layers)
    # Berechne die Anzahl der Spalten und Zeilen
    num_cols = ceil(sqrt(num_layers))+1
    num_rows = ceil(num_layers / num_cols)
    
    spritesheet_width = sprite_width * num_cols
    spritesheet_height = sprite_height * num_rows
    spritesheet = Image.new("RGBA", (spritesheet_width, spritesheet_height))
    
    for index, layer in enumerate(layers):
        col = index % num_cols
        row = index // num_cols
        x = col * sprite_width
        y = row * sprite_height
        spritesheet.paste(layer, (x, y))

    spritesheet.save(output_file, format="PNG")

def process_multiple_psd_files(psd_files, output_file, sprite_width, sprite_height):
    all_layers = []
    for psd_file in psd_files:
        layers = extract_visible_layers_from_psd(psd_file, sprite_width, sprite_height)
        all_layers.extend(layers)

    create_spritesheet(all_layers, output_file, sprite_width, sprite_height)

# Beispielverwendung
psd_files = ['Sing_With_Me_3.psd']  # Liste von PSD-Dateien
output_file = 'Sing_With_Me_3.png'
sprite_width = 318  # Breite jedes einzelnen Sprites
sprite_height = 318  # Höhe jedes einzelnen Sprites

process_multiple_psd_files(psd_files, output_file, sprite_width, sprite_height)
