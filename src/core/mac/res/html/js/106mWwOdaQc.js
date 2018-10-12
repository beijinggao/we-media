if (self.CavalryLogger) { CavalryLogger.start_js(["LytNC"]); }

__d("isFbDotComURI",[],(function(a,b,c,d,e,f){var g=new RegExp("(^|\\.)fb\\.com?$","i"),h=["http","https"];function a(a){if(a.isEmpty()&&a.toString()!=="#")return!1;return!a.getDomain()&&!a.getProtocol()?!1:h.indexOf(a.getProtocol())!==-1&&g.test(a.getDomain())}e.exports=a}),null);