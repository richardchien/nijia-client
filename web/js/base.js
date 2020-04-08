document.body.ondragstart = () => false
document.body.ondrop = () => false

document.addEventListener('contextmenu', e => {
    console.log(e)
    e.preventDefault()
})

function createWebChannel(callback) {
    new QWebChannel(qt.webChannelTransport,
        channel => {
            window.thisWidget = channel.objects.thisWidget
            window.globalData = channel.objects.globalData
            callback(channel)
        }
    )
}
