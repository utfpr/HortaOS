var App = {
  baseUrl: "https://thingspeak.com/channels/370192/charts/{chartNumber}?width=420&height=225&title=Monitoramento",
  iframe: document.getElementById('graph-iframe'),
  selector: document.getElementById('graph-selector'),
  init: function() {
    const self = this;
    this.selector.addEventListener('change', function() {
      self.updateIframe();
    });
  },
  getChartUrl: function() {
    const value = this.selector.value;
    return this.baseUrl.replace('{chartNumber}', value);
  },
  updateIframe: function() {
    const url = this.getChartUrl();
    this.iframe.src = url;
  }
};

App.init();
