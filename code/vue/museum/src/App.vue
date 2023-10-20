<template>
  <div id="app">
    <!-- <museum></museum> -->
    <!-- <TestComponent></TestComponent> -->
    <objectTrace></objectTrace>
  </div>
</template>

<script>
import objectTrace from './components/objectTrace.vue'
// import museum from './components/museum.vue'
// import TestComponent from './components/TestComponent.vue'

export default {
  name: 'App',
  components: {
    objectTrace
    // museum
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
