from PIL import Image, ImageDraw
from numpy import array, exp, pi, sqrt, uint8, cos

#%% =============================================================================
# Functions of creating images 
# =============================================================================
def generate_circle(center=(0.5,0.5), ray=0.5, channels=[1,1,1], img_size=(256,256), profil='uniform', ecart_type=32):
    ### Case of uniform color distribution
    if profil=='uniform':
        # Initializate a BMP with RGB format (3 channels)
        grd = Image.new(mode='RGB', size=img_size, color=(0,0,0)) 
        # Opening a drawning instance from our background
        draw = ImageDraw.Draw(grd)       
        # Red Circle (or elipse if lenght!=height) in south-west corner
        draw.ellipse(
            xy=(
                int(abs(center[0]-ray)*img_size[0]), int(abs(center[0]-ray)*img_size[1]), int(abs(center[0]+ray)*img_size[0]), int(abs(center[0]+ray)*img_size[1])
                ), 
            fill=tuple([255*i for i in channels]), 
            outline=(0, 0, 0)
            )
        return grd
    
if __name__=="__main__":
    M = 512
    source  = generate_circle(img_size=(M,M))
    source.save("source_512x512.png")
    