a = ["/../cam/img1.jpg", "/../cam/img2.jpg","/../cam/img3.jpg","/../cam/img4.jpg","/../cam/img5.jpg", "/../cam/img6.jpg"]


//Modify the src attribute of the image with the ID "myImage"
const fs = require('fs')

const content = JSON.stringify(a)

try {
const data = fs.writeFileSync('app/public/js/history.txt', content)
//file written successfully
} catch (err) {
console.error(err)
}