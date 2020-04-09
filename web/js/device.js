const params = new URLSearchParams(document.location.search)
const uid = params.get('uid')
console.log(`this page is device '${uid}'`)

let device = window.device = {
    uid: uid,
    name: '设备名称',
    model: '',
    switchable: false,
    state: {}
}

function setupDevice() {
    globalData.device(uid, dev => Object.assign(device, dev))
    globalData.deviceListChanged.connect(() => {
        globalData.device(uid, dev => Object.assign(device, dev))
    })
}
