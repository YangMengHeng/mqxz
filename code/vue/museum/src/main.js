import Vue from 'vue'
import App from './App.vue'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
import axios from 'axios'
import qs from 'qs'


axios.defaults.baseURL = 'http://192.168.1.242:8760'
axios.defaults.headers['Authorization'] = 'Basic bGFtcF93ZWI6bGFtcF93ZWJfc2VjcmV0'
axios.defaults.headers['tenant'] = 'MDAwMA=='
// axios.defaults.headers['token'] = localStorage.getItem('token')
axios.defaults.headers['token'] ='Bearer test'
axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';
axios.defaults.headers.get['Content-Type'] = 'application/x-www-form-urlencoded';

Vue.use(ElementUI)

Vue.config.productionTip = false
Vue.prototype.$axios = axios
Vue.prototype.$qs = qs

new Vue({
  el: '#app',
  render: h => h(App),
})
