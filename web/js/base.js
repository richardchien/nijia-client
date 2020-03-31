document.body.ondragstart = () => false;
document.body.ondrop = () => false;

document.addEventListener('contextmenu', e => {
    console.log(e);
    e.preventDefault();
});

new QWebChannel(qt.webChannelTransport,
    channel => window.bridge = channel.objects.bridge
);
