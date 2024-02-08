import os, sys
if "__main__" == __name__ :
    for i in range(1,220):
        I = "0"*(3-len(str(i)))+str(i)
        cmmnd = "wget -O I_{}.jpg    http://image.calameo.abcvg.info/image.php?image=https://p.calameoassets.com/200316134826-8aff10b1e03f320a4cfb6aa5ce6b39d8/p{}.jpg".format(I,I)
        cmmnd = "wget -O I_{}.jpg    https://p.calameoassets.com/200316134826-8aff10b1e03f320a4cfb6aa5ce6b39d8/p{}.jpg".format(I,I)
        cmmnd = "wget -O I_{}.jpg    https://p.calameoassets.com/200316134826-8aff10b1e03f320a4cfb6aa5ce6b39d8/p{}.jpg".format(I,i)
        # print(I)
        os.system(cmmnd)
    os.system("convert I_*.jpg Edito.pdf")
    os.system("rm I_*.jpg")
    # convert -compress jpeg I_*.jpg my_jpegs.pdf
    # convert I_*.jpg my_jpegs.pdf
    # convert: negative or zero image size `I_027.jpg' @ error/image.c/SetImageExtent/2703.
    
    # convert: no decode delegate for this image format `I_027.jpg' @ error/svg.c/ReadSVGImage/3409.

    # convert I_[0]*.jpg my_jpegs.pdf
    # identify  -ping -format '%w %h' I_099.jpg 
    