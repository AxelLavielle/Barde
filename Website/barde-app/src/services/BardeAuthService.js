import Vue from 'vue'

export default {
  register() {
    return  Vue.http.post('/auth/register', body).then(successCallback,
      errorCallback);
  }
}
