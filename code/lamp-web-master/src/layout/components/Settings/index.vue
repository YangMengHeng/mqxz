<template>
  <div class="drawer-container">
    <div>
      <h3 class="drawer-title">
        {{ $t('settings.title') }}
      </h3>
      <div class="drawer-item">
        <span>{{ $t('settings.theme') }}</span>
        <theme-picker
          style="float: right;height: 26px;margin: -3px 8px 0 0;"
          @change="themeChange"
        />
      </div>

      <div class="drawer-item">
        <span>{{ $t('settings.uniqueOpened') }}</span>
        <el-switch
          v-model="uniqueOpened"
          class="drawer-switch"
        />
      </div>

      <div class="drawer-item">
        <span>{{ $t('settings.tagsView') }}</span>
        <el-switch
          v-model="tagsView"
          class="drawer-switch"
        />
      </div>

      <div class="drawer-item">
        <span>{{ $t('settings.fixedHeader') }}</span>
        <el-switch
          v-model="fixedHeader"
          class="drawer-switch"
        />
      </div>

      <div class="drawer-item">
        <span>{{ $t('settings.sidebarLogo') }}</span>
        <el-switch
          v-model="sidebarLogo"
          class="drawer-switch"
        />
      </div>
    </div>
  </div>
</template>

<script>
import ThemePicker from '@/components/ThemePicker'

export default {
  components: { ThemePicker },
  data () {
    return {}
  },
  computed: {
    fixedHeader: {
      get () {
        return this.$store.state.setting.fixHeader
      },
      set (val) {
        this.$store.commit('setting/fixHeader', val)
      }
    },
    tagsView: {
      get () {
        return this.$store.state.setting.multipage
      },
      set (val) {
        this.$store.commit('setting/setMultipage', val)
      }
    },
    sidebarLogo: {
      get () {
        return this.$store.state.setting.sidebarLogo
      },
      set (val) {
        this.$store.commit('setting/setSidebarLogo', val)
      }
    },
    uniqueOpened: {
      get () {
        return this.$store.state.setting.uniqueOpened
      },
      set (val) {
        this.$store.commit('setting/setUniqueOpened', val)
      }
    }
  },
  methods: {
    themeChange (val) {
      this.$store.commit('setting/setTheme', val)
    }
  }
}
</script>

<style lang="scss" scoped>
.drawer-container {
  padding: 24px;
  font-size: 14px;
  line-height: 1.5;
  word-wrap: break-word;

  .drawer-title {
    margin-bottom: 12px;
    color: rgba(0, 0, 0, 0.85);
    font-size: 14px;
    line-height: 22px;
  }

  .drawer-item {
    color: rgba(0, 0, 0, 0.65);
    font-size: 14px;
    padding: 12px 0;
  }

  .drawer-switch {
    float: right;
  }
}
</style>
